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

#include <array_data_encoder.h>
#include <array_source_block_encoder.h>
#include <parameters/fec_parameters.h>
#include <vector>

fec_parameters
array_data_encoder::get_fec_parameters(void) const
{
    return m_fec_params;
}

array_source_block_encoder
array_data_encoder::get_source_block(int sbn) const
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

int
array_data_encoder::symbol_size(void) const
{
    return m_fec_params.symbol_size();
}

int
array_data_encoder::number_of_source_blocks(void) const
{
    return m_fec_params.num_source_blocks();
}

std::vector<array_source_block_encoder>
array_data_encoder::get_source_block_encoders(void)
{
    // TODO(pbhandari): actually make this work
    return std::vector<array_source_block_encoder> {};
}
