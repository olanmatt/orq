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

#ifndef INCLUDE_PARAMETERS_PARAMETER_CHECKER_H_
#define INCLUDE_PARAMETERS_PARAMETER_CHECKER_H_

#include <parameters/internal_constants.h>
#include <parameters/internal_functions.h>
#include <util/extra_math.h>

#include <algorithm>

class parameter_checker
{
public:
    static bool is_data_length_out_of_bounds(uint64_t dataLen);
    static uint64_t max_allowed_data_length(uint16_t symbSize);
    static bool is_symbol_size_out_of_bounds(uint16_t symbSize);
    static uint16_t min_allowed_symbol_size(uint64_t dataLen);
    static bool is_num_source_blocks_out_of_bounds(uint8_t numSrcBs);
    static uint8_t min_allowed_num_source_blocks(uint64_t dataLen,
            uint16_t symbSize);
    static uint8_t max_allowed_num_source_blocks(uint64_t dataLen,
            uint16_t symbSize);
    static bool is_interleaver_length_out_of_bounds(uint16_t interLen);
    static uint16_t max_allowed_interleaver_length(uint16_t symbSize);
    static bool are_valid_fec_parameters(uint64_t dataLen, uint16_t symbSize,
                                         uint8_t numSrcBs, uint16_t interLen);
    static bool is_payload_length_out_of_bounds(uint16_t payLen);
    static uint16_t min_allowed_payload_length(uint64_t dataLen);
    static uint64_t min_decoding_block_size();
    static uint64_t min_allowed_decoding_block_size(uint64_t dataLen,
            uint16_t payLen);
    static uint64_t max_allowed_data_length(uint16_t payLen, uint64_t maxDBMem);
    static bool are_valid_deriver_parameters(uint64_t dataLen, uint16_t payLen,
            uint64_t maxDBMem);
    static bool is_source_block_number_out_of_bounds(uint8_t sbn);
    static bool is_encoding_symbol_id_out_of_bounds(uint32_t esi);
    static bool is_valid_fec_payload_id(uint8_t sbn, uint32_t esi,
                                        uint8_t numSrcBs);
    static bool is_num_source_symbols_per_block_out_of_bounds(uint16_t numSrcSymbs);
    static uint32_t num_repair_symbols_per_block(uint16_t numSrcSymbs);

private:
    static uint64_t _max_allowed_data_length(uint16_t T);
    static uint16_t _min_allowed_symbol_size(uint64_t F);
    static uint16_t _min_allowed_num_source_blocks(uint16_t Kt);
    static uint16_t _max_allowed_num_source_blocks(uint16_t Kt);
    static uint16_t _max_allowed_interleaver_length(uint16_t T);
    static uint64_t _min_allowed_decoding_block_size(uint64_t F, uint16_t T);
    static uint64_t _max_allowed_data_length(uint16_t T, uint64_t WS);
    static bool _are_data_length_and_symbol_size_out_of_bounds(uint64_t F,
            uint16_t T);
    static bool _are_data_length_and_payload_length_out_of_bounds(uint64_t F,
            uint16_t P);
    static void _check_data_length_out_of_bounds(uint64_t F);
    static void _check_symbol_size_out_of_bounds(uint16_t T);
    static void _check_data_length_and_symbol_size_out_of_bounds(uint64_t F,
            uint16_t T);
    static void _check_num_source_blocks_out_of_bounds(uint8_t Z);
    static void _check_payload_length_out_of_bounds(uint16_t P);
    static void _check_data_length_and_payload_length_out_of_bounds(uint64_t F,
            uint16_t P);
    static void _check_decoding_block_size_out_of_bounds(uint64_t WS);
    static void _check_num_source_symbols_per_block_out_of_bounds(uint16_t K);
};

#endif  // INCLUDE_PARAMETERS_PARAMETER_CHECKER_H_
