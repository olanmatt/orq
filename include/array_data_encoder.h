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

#ifndef INCLUDE_ARRAY_DATA_ENCODER_H_
#define INCLUDE_ARRAY_DATA_ENCODER_H_

#include <array_source_block_encoder.h>
#include <parameters/fec_parameters.h>
#include <vector>

class array_data_encoder
{
public:
    static array_data_encoder new_encoder(std::vector<uint8_t> data,
                                          int offset,
                                          fec_parameters fec_params)
    {
        throw "Use the constructor";
    }


    fec_parameters get_fec_parameters(void) const;

    array_source_block_encoder get_source_block(int sbn) const;

    std::vector<array_source_block_encoder> get_source_block_iterable(void) const;

    std::vector<uint8_t> get_data_array(void) const;

    int get_data_offset(void) const;

    int symbol_size(void) const;

    uint64_t data_length() const;

    int number_of_source_blocks(void) const;

    array_data_encoder(std::vector<uint8_t> array, int offset,
                       fec_parameters fecParams)
        : m_array(array), m_offset(offset), m_fec_params(fecParams),
          m_src_block_encoders(get_source_block_encoders())
    { }

private:
    static std::vector<array_source_block_encoder> get_source_block_encoders(void);

    const std::vector<uint8_t> m_array;
    const int m_offset;
    const fec_parameters m_fec_params;
    const std::vector<array_source_block_encoder> m_src_block_encoders;
};

#endif  // INCLUDE_ARRAY_DATA_ENCODER_H_
