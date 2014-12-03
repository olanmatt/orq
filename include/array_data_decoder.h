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

#ifndef INCLUDE_ARRAY_DATA_DECODER_H_
#define INCLUDE_ARRAY_DATA_DECODER_H_

#include <array_source_block_decoder.h>
#include <parameters/fec_parameters.h>

#include <vector>

class array_data_decoder
{
public:
    static array_data_decoder
    new_decoder(fec_parameters fecParams, int extraSymbols)
    {
        throw "Use the constructor";
    }

    fec_parameters get_fec_parameters(void) const;

    uint64_t data_length(void) const;
    uint16_t symbol_size(void) const;
    uint8_t number_of_source_blocks(void) const;

    bool is_data_decoded(void) const;

    std::vector<uint8_t> get_data_array(void) const;

    // XXX(olanmatt):
    array_data_decoder(std::vector<uint8_t> data_array, fec_parameters params,
                       uint16_t extra_symbols);

private:
    const std::vector<uint8_t> dataArray;
    const fec_parameters fec_params;
    const std::vector<array_source_block_decoder> m_src_block_decoders;
};
#endif  // INCLUDE_ARRAY_DATA_DECODER_H_
