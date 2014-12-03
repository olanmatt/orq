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

#ifndef INCLUDE_ARRAY_SOURCE_BLOCK_DECODER_H_
#define INCLUDE_ARRAY_SOURCE_BLOCK_DECODER_H_

class array_data_decoder;

#include <encoding_symbol.h>
#include <encoding_packet.h>
#include <padded_byte_array.h>
#include <sbd_info.h>
#include <symbols_state.h>
#include <source_block_state.h>
#include <parameters/fec_parameters.h>
#include <parameters/internal_constants.h>

#include <iterator>
#include <map>
#include <memory>
#include <set>
#include <vector>

class array_source_block_decoder
{
public:
    // requires valid arguments
    static array_source_block_decoder
    new_decoder(const array_data_decoder &dataDecoder,
                std::vector<uint8_t> array, int arrayOff,
                fec_parameters fecParams, int sbn, int K, int extraSymbols)
    {
        throw "Use constructor.";
    }

    array_data_decoder get_data_decoder(void) const;

    uint8_t get_source_block_number(void) const;
    uint16_t get_number_of_source_symbols(void) const;

    bool contains_source_symbol(uint32_t esi) const;
    bool contains_repair_symbol(uint32_t esi) const;
    bool is_source_block_decoded(void) const;

    source_block_state latest_state(void) const;

    // XXX(olanmatt): std::set<uint8_t> ?
    std::set<uint8_t> missing_source_symbols(void) const;
    std::set<uint8_t> available_repair_symbols(void) const;

    sbd_info information(void) const;
    source_block_state put_encoding_packet(encoding_packet packet);

    // ============================= TEST_CODE ============================= //

    static source_block_state force_decode(array_source_block_decoder decoder);

    array_source_block_decoder(std::shared_ptr<array_data_decoder> data_decoder,
                               padded_byte_array data, uint8_t sbn, uint16_t K,
                               int extra_symbols)
        : m_data_decoder(data_decoder), m_data(data), m_source_block_number(sbn),
          m_K(K), m_symbols_state(K, extra_symbols)
    {};
private:
    fec_parameters get_fec_parameters(void) const;
    void check_source_symbol_esi(uint32_t esi) const;
    void check_repair_symbol_esi(uint32_t esi) const;

    /* ===== Requires locked symbolsState! ===== */
    void decode(void);
    std::set<uint8_t> get_missing_source_symbols(void) const;
    std::set<uint8_t> get_available_repair_symbols(void) const;
    void put_source_data(uint32_t esi, std::vector<uint8_t> symbolData,
                         int off = 0);
    bool put_repair_data(uint32_t esi, std::vector<uint8_t> symbolData);
    const std::vector< std::vector<uint8_t> >
    generate_intermediate_symbols(void) const;

    // variables
    const std::shared_ptr<array_data_decoder> m_data_decoder;
    const padded_byte_array m_data;

    const uint8_t m_source_block_number;
    const uint16_t m_K;
    const symbols_state m_symbols_state;
};
#endif  // INCLUDE_ARRAY_SOURCE_BLOCK_DECODER_H_
