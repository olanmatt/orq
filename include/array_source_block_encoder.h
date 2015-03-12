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

#ifndef INCLUDE_ARRAY_SOURCE_BLOCK_ENCODER_H_
#define INCLUDE_ARRAY_SOURCE_BLOCK_ENCODER_H_

class array_data_encoder;

#include <encoding_symbol.h>
#include <encoding_packet.h>
#include <parameters/fec_parameters.h>
#include <parameters/internal_constants.h>

#include <memory>
#include <vector>
#include <iterator>

class array_source_block_encoder
{
public:
    // requires valid arguments
    static array_source_block_encoder
    new_encoder(const array_data_encoder &data_encoder,
                std::vector< std::vector<uint8_t> > array, int array_offset,
                fec_parameters fec_params, int source_block_num, int K)
    {
        throw "Use the constructor";
    }

    static std::vector< std::shared_ptr<encoding_symbol> >
    prepare_source_symbols(std::vector<uint8_t> array, int array_offset,
                           fec_parameters fec_params, uint16_t K);

    uint8_t get_source_block_number(void) const;

    uint16_t get_number_source_symbols(void) const;

    encoding_packet get_encoding_packet(uint32_t esi) const;

    encoding_packet source_packet(uint32_t esi) const;
    encoding_packet source_packet(uint32_t esi, uint16_t num_symbols) const;

    encoding_packet repair_packet(uint32_t esi) const;
    encoding_packet repair_packet(uint32_t esi, uint16_t num_symbols) const;

    array_source_block_encoder(fec_parameters fec_params,
                               std::vector< std::shared_ptr<encoding_symbol> > source_symbols,
                               uint8_t source_block_number, uint16_t K);

private:
    // requires valid ESI
    repair_symbol get_repair_symbol(uint32_t esi) const;

    // use only this method for access to the intermediate symbols
    std::vector< std::vector<uint8_t> > get_intermediate_symbols() const;

    uint8_t m_source_block_number;
    uint16_t m_K;
    uint16_t m_Kprime;
    fec_parameters m_fec_params;
    std::vector< std::shared_ptr<encoding_symbol> > m_source_symbols;
    std::vector< std::vector<uint8_t> > m_intermediate_symbols;
};

#endif  // INCLUDE_ARRAY_SOURCE_BLOCK_ENCODER_H_
