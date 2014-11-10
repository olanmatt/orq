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

#include <data_utils.h>
#include <array_data_encoder.h>
#include <array_source_block_encoder.h>
#include <partition.h>
#include <parameters/fec_parameters.h>
#include <memory>
#include <vector>

fec_parameters
array_data_encoder::get_fec_parameters(void) const
{
    return m_fec_params;
}

array_source_block_encoder
array_data_encoder::get_source_block(uint16_t sbn) const
{
    return m_src_block_encoders[sbn];
}

std::vector<array_source_block_encoder>
array_data_encoder::get_source_block_iterable(void) const
{
    return m_src_block_encoders;
}

std::vector<uint8_t>
array_data_encoder::get_data_array(void) const
{
    return m_array;
}

int
array_data_encoder::get_data_offset(void) const
{
    return m_offset;
}

uint64_t
array_data_encoder::data_length(void) const
{
    return m_fec_params.data_length();
}

uint16_t
array_data_encoder::symbol_size(void) const
{
    return m_fec_params.symbol_size();
}

uint8_t
array_data_encoder::number_of_source_blocks(void) const
{
    return m_fec_params.num_source_blocks();
}

std::vector<array_source_block_encoder>
array_data_encoder::get_source_block_encoders(void)
{
    const uint16_t Kt = m_fec_params.total_symbols();
    const uint16_t Z = m_fec_params.num_source_blocks();
    const uint16_t T = m_fec_params.symbol_size();

    const partition kz = partition(Kt, Z);
    const int k_IL = kz.IL();
    const int k_IS = kz.IS();
    const int k_JL = kz.JL();

    std::vector<array_source_block_encoder> source_blocks;

    int sbn = 0;
    int offset = m_offset;

    for ( ; sbn < k_JL; sbn++, offset += k_IL * T) {
        source_blocks.push_back(get_encoder(offset, sbn, k_IL));
    }

    for ( ; sbn < Z; sbn++, offset += k_IS * T) {
        source_blocks.push_back(get_encoder(offset, sbn, k_IS));
    }

    return source_blocks;
}

array_source_block_encoder
array_data_encoder::get_encoder(int offset, uint16_t source_block_num, uint16_t K)
{
    auto symbol = array_source_block_encoder::prepare_source_symbols(
                      m_array, offset, m_fec_params, K);

    return array_source_block_encoder(std::shared_ptr<array_data_encoder>(this),
                                      symbol, source_block_num, K);
}
