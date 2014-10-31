/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Matt Olan
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

#ifndef INCLUDE_PARAMETERS_FEC_PARAMETERS_H_
#define INCLUDE_PARAMETERS_FEC_PARAMETERS_H_

#include <parameters/internal_constants.h>
#include <parameters/internal_functions.h>
#include <parameters/parameter_checker.h>
#include <parameters/parameter_io.h>
#include <util/octet_ops.h>

class fec_parameters
{
public:
    static fec_parameters new_parameters(uint64_t data_len, uint16_t symbol_size,
                                         uint8_t num_source_blocks);

    static fec_parameters new_parameters(uint64_t data_len, uint16_t symbol_size,
                                         uint8_t num_source_blocks, uint16_t inter_len);

    static fec_parameters derive_parameters(uint64_t data_len, uint16_t pay_len,
                                            uint64_t max_db_mem);
    static fec_parameters new_local_instance(uint64_t F, uint16_t T, uint16_t Z,
            uint16_t N, uint8_t Al);

    uint64_t data_length();
    uint16_t symbol_size();
    uint16_t num_source_blocks();
    uint16_t interleaver_length();
    uint8_t symbol_alignment();
    uint16_t total_symbols();

private:
    static uint16_t derive_Z(uint32_t Kt, uint64_t WS, uint16_t T, uint8_t Al,
                             uint16_t topN);

    static uint16_t derive_N(uint32_t Kt, uint16_t Z, uint64_t WS, uint16_t T,
                             uint8_t Al,
                             uint16_t topN);

    fec_parameters(uint64_t common_fec_oti, uint32_t scheme_spec_fec_oti);
    uint64_t common_fec_oti_;
    uint32_t scheme_spec_fec_oti_;
};

#endif  // INCLUDE_PARAMETERS_FEC_PARAMETERS_H_
