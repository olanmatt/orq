/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Matt Olan, Prajjwal Bhandari
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <array_source_block_encoder.h>
#include <array_data_encoder.h>
#include <encoding_symbol.h>
#include <encoding_packet.h>
#include <linear_system.h>
#include <parameters/fec_parameters.h>
#include <padded_byte_array.h>
#include <tuple.h>

#include <memory>
#include <vector>
#include <iterator>
#include <algorithm>


// TODO(pbhandari): create a constructor that doesn't take in pointers
array_source_block_encoder::array_source_block_encoder(
    fec_parameters fec_params,
    std::vector< std::shared_ptr<encoding_symbol> > source_symbols,
    uint8_t source_block_number, uint16_t K)

    : m_source_block_number(source_block_number), m_K(K),
      m_Kprime(systematic_indices::ceil(K)),
      m_fec_params(fec_params), m_source_symbols(source_symbols)
{ }

/*static*/ std::vector< std::shared_ptr<encoding_symbol> >
array_source_block_encoder::prepare_source_symbols(std::vector<uint8_t> array,
        int array_offset, fec_parameters fec_params, uint16_t K)
{
    uint16_t T = fec_params.symbol_size();
    int array_size = array.size();
    int symbol_offset = array_offset;

    std::vector< std::shared_ptr<encoding_symbol> > symbol;

    for (int esi = 0; esi < K; esi++, symbol_offset += T) {
        uint16_t symbol_len = std::min(static_cast<int>(T),
                                       array_size - symbol_offset);
        padded_byte_array symbol_data(array, symbol_offset, symbol_len, T);

        symbol.push_back(std::shared_ptr<encoding_symbol>(
                             new source_symbol(esi, symbol_data)));
    }

    return symbol;
}

uint8_t
array_source_block_encoder::get_source_block_number(void) const
{
    return m_source_block_number;
}

uint16_t
array_source_block_encoder::get_number_source_symbols(void) const
{
    return m_K;
}

encoding_packet
array_source_block_encoder::get_encoding_packet(uint32_t esi) const
{
    symbol smb = esi < m_K ? symbol::SOURCE : symbol::REPAIR;

    if (esi >= internal_constants::ESI_max) {
        throw std::invalid_argument("invalid encoding symbol id");
    }

    return encoding_packet(m_source_block_number, esi,
                           m_source_symbols[esi]->transport_data(), 1, smb);
}

encoding_packet
array_source_block_encoder::source_packet(uint32_t esi) const
{
    if (esi >= m_K) {
        throw std::invalid_argument("invalid encoding symbol id");
    }
    return encoding_packet(m_source_block_number, esi,
                           m_source_symbols[esi]->transport_data(), 1,
                           symbol::SOURCE);
}

encoding_packet
array_source_block_encoder::source_packet(uint32_t esi,
        uint16_t num_symbols) const
{
    if (esi >= m_K) {
        throw std::invalid_argument("invalid encoding symbol id");
    }

    if (!num_symbols || num_symbols > m_K - esi) {
        throw std::invalid_argument("invalid number of source symbols");
    }

    std::vector<uint8_t> symbols;
    for (int ctr = 0, idx = esi; ctr < num_symbols; ctr++, idx++) {
        symbols.insert(symbols.end(),
                       m_source_symbols[idx]->transport_data().begin(),
                       m_source_symbols[idx]->transport_data().end());
    }

    // TODO(pbhandari): symbols.flip();


    return encoding_packet(m_source_block_number, esi, symbols, num_symbols,
                           symbol::SOURCE);
}

encoding_packet
array_source_block_encoder::repair_packet(uint32_t esi) const
{
    if (esi < m_K || esi > internal_constants::ESI_max) {
        throw std::invalid_argument("invalid repair symbol esi");
    }

    return encoding_packet(m_source_block_number, esi,
                           m_source_symbols[esi]->transport_data(), 1,
                           symbol::REPAIR);
}
encoding_packet
array_source_block_encoder::repair_packet(uint32_t esi,
        uint16_t num_symbols) const
{
    if (esi > internal_constants::ESI_max) {
        throw std::invalid_argument("invalid repair symbol esi");
    }

    if (!num_symbols || num_symbols > 1 + internal_constants::ESI_max - esi) {
        throw std::invalid_argument("invalid number of source symbols");
    }

    std::vector<uint8_t> symbols;
    for (int ctr = 0; ctr < num_symbols; ctr++) {
        symbols.insert(symbols.end(),
                       get_repair_symbol(esi + 1).transport_data().begin(),
                       get_repair_symbol(esi + 1).transport_data().end());
    }

    return encoding_packet(m_source_block_number, esi, symbols, num_symbols,
                           symbol::REPAIR);
}

/*********************************************************************
 *                    PRIVATE METHODS START HERE                     *
 *********************************************************************/

// requires valid ESI
repair_symbol
array_source_block_encoder::get_repair_symbol(uint32_t esi) const
{
    const tuple tpl(m_Kprime, esi + (m_Kprime - m_K));

    std::vector<uint8_t> enc_data =
        linear_system::enc(m_Kprime, get_intermediate_symbols(), tpl,
                           m_fec_params.symbol_size());

    return repair_symbol(esi, enc_data);
}

// use only this method for access to the intermediate symbols
std::vector< std::vector<uint8_t> >
array_source_block_encoder::get_intermediate_symbols() const
{
    auto Ki = systematic_indices::get_k_index(m_Kprime);
    auto S = systematic_indices::S(Ki);
    auto H = systematic_indices::H(Ki);

    // generate LxL Constraint Matrix
    auto constraint_matrix = linear_system::generate_constraint_matrix(m_Kprime);

    // TODO(pbhandari): L and T used to preallocate size of D
    /* auto L = m_Kprime + S + H; */
    /* auto T = get_fec_parameters().symbol_size(); */

    // allocate and initialize vector D
    std::vector< std::vector<uint8_t> > D(m_Kprime + S + H);
    for (uint32_t row = S + H, index = 0; row < m_K + S + H; row++, index++) {
        D[row] = m_source_symbols[index]->data();
    }

    // solve system of equations
    return linear_system::P_inactivation_decoding(constraint_matrix, D, m_Kprime);
}
