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

#include <parameters/parameter_checker.h>

#include <algorithm>

bool parameter_checker::is_data_length_out_of_bounds(uint64_t dataLen)
{
    return !(internal_constants::F_min <= dataLen
             && dataLen <= internal_constants::F_max);
}

uint64_t parameter_checker::max_allowed_data_length(uint16_t symbSize)
{
    _check_symbol_size_out_of_bounds(symbSize);
    return _max_allowed_data_length(symbSize);
}

bool parameter_checker::is_symbol_size_out_of_bounds(uint16_t symbSize)
{
    return !(internal_constants::T_min <= symbSize
             && symbSize <= internal_constants::T_max);
}

uint16_t parameter_checker::min_allowed_symbol_size(uint64_t dataLen)
{
    _check_data_length_out_of_bounds(dataLen);
    return _min_allowed_symbol_size(dataLen);
}

bool parameter_checker::is_num_source_blocks_out_of_bounds(uint8_t numSrcBs)
{
    // TODO(olanmatt): Verify overflow control that throws warning.
    return !(internal_constants::Z_min <=
             numSrcBs);  // && numSrcBs <= internal_constants::Z_max);
}

uint8_t parameter_checker::min_allowed_num_source_blocks(uint64_t dataLen,
        uint16_t symbSize)
{
    _check_data_length_out_of_bounds(dataLen);
    _check_symbol_size_out_of_bounds(symbSize);
    _check_data_length_and_symbol_size_out_of_bounds(dataLen, symbSize);

    uint32_t Kt = internal_functions::get_total_symbols(dataLen, symbSize);
    return _min_allowed_num_source_blocks(Kt);
}

uint8_t parameter_checker::max_allowed_num_source_blocks(uint64_t dataLen,
        uint16_t symbSize)
{
    _check_data_length_out_of_bounds(dataLen);
    _check_symbol_size_out_of_bounds(symbSize);
    _check_data_length_and_symbol_size_out_of_bounds(dataLen, symbSize);

    uint16_t Kt = internal_functions::get_total_symbols(dataLen, symbSize);
    return _max_allowed_num_source_blocks(Kt);
}

bool parameter_checker::is_interleaver_length_out_of_bounds(uint16_t interLen)
{
    return !(internal_constants::N_min <= interLen
             && interLen <= internal_constants::N_max);
}

uint16_t parameter_checker::max_allowed_interleaver_length(uint16_t symbSize)
{
    _check_symbol_size_out_of_bounds(symbSize);
    return _max_allowed_interleaver_length(symbSize);
}

bool parameter_checker::are_valid_fec_parameters(uint64_t dataLen,
        uint16_t symbSize, uint8_t numSrcBs, uint16_t interLen)
{
    uint64_t F = dataLen;
    uint16_t T = symbSize;
    uint8_t Z = numSrcBs;
    uint16_t N = interLen;

    if (is_data_length_out_of_bounds(F)) {
        return false;
    }
    if (is_symbol_size_out_of_bounds(T)) {
        return false;
    }
    if (is_num_source_blocks_out_of_bounds(Z)) {
        return false;
    }
    if (is_interleaver_length_out_of_bounds(N)) {
        return false;
    }

    if (_are_data_length_and_symbol_size_out_of_bounds(F, T)) {
        return false;
    }

    int Kt = internal_functions::get_total_symbols(F, T);
    int minAllowedZ = _min_allowed_num_source_blocks(Kt);
    int maxAllowedZ = _max_allowed_num_source_blocks(Kt);

    if (Z < minAllowedZ || Z > maxAllowedZ) {
        return false;
    }

    int maxAllowedN = _max_allowed_interleaver_length(T);

    if (N > maxAllowedN) {
        return false;
    }

    return true;
}

bool parameter_checker::is_payload_length_out_of_bounds(uint16_t payLen)
{
    return !(internal_constants::T_min <= payLen
             && payLen <= internal_constants::T_max);
}

uint16_t parameter_checker::min_allowed_payload_length(uint64_t dataLen)
{
    return min_allowed_symbol_size(dataLen);
}

uint64_t parameter_checker::min_decoding_block_size()
{
    return _min_allowed_decoding_block_size(internal_constants::F_min,
                                            internal_constants::T_min);
}

uint64_t parameter_checker::min_allowed_decoding_block_size(uint64_t dataLen,
        uint16_t payLen)
{
    _check_data_length_out_of_bounds(dataLen);
    _check_payload_length_out_of_bounds(payLen);
    _check_data_length_and_payload_length_out_of_bounds(dataLen, payLen);

    return _min_allowed_decoding_block_size(dataLen, payLen);
}

uint64_t parameter_checker::max_allowed_data_length(uint16_t payLen,
        uint64_t maxDBMem)
{
    _check_payload_length_out_of_bounds(payLen);
    _check_decoding_block_size_out_of_bounds(maxDBMem);
    if (maxDBMem < payLen) {
        throw std::invalid_argument("maximum decoding block size must be at least equal to the payload length");
    }

    return _max_allowed_data_length(payLen, maxDBMem);
}

bool parameter_checker::are_valid_deriver_parameters(uint64_t dataLen,
        uint16_t payLen, uint64_t maxDBMem)
{
    long F = dataLen;
    int T = payLen;
    long WS = maxDBMem;

    if (is_data_length_out_of_bounds(F)) {
        return false;
    }
    if (is_symbol_size_out_of_bounds(T)) {
        return false;
    }

    long absolMinWS = min_decoding_block_size();
    if (WS < absolMinWS) {
        return false;
    }

    int minT = _min_allowed_symbol_size(F);
    if (T < minT) {
        return false;
    }

    long minWS = _min_allowed_decoding_block_size(F, T);
    if (WS < minWS) {
        return false;
    }

    return true;
}

bool parameter_checker::is_source_block_number_out_of_bounds(uint8_t sbn)
{
    return !(internal_constants::SBN_min <= sbn
             && sbn <= internal_constants::SBN_max);
}

bool parameter_checker::is_encoding_symbol_id_out_of_bounds(uint32_t esi)
{
    // TODO(olanmatt): Verify overflow control that throws warning.
    return !(esi <=
             internal_constants::ESI_max);  // && internal_constants::ESI_min <= esi
}

bool parameter_checker::is_valid_fec_payload_id(uint8_t sbn, uint32_t esi,
        uint8_t numSrcBs)
{
    _check_num_source_blocks_out_of_bounds(numSrcBs);

    if (sbn < internal_constants::SBN_min || sbn >= numSrcBs) {
        return false;
    }
    if (is_encoding_symbol_id_out_of_bounds(esi)) {
        return false;
    }

    return true;
}

bool parameter_checker::is_num_source_symbols_per_block_out_of_bounds(
    uint16_t numSrcSymbs)
{
    return !(internal_constants::K_min <= numSrcSymbs
             && numSrcSymbs <= internal_constants::K_max);
}

uint32_t parameter_checker::num_repair_symbols_per_block(uint16_t numSrcSymbs)
{
    _check_num_source_symbols_per_block_out_of_bounds(numSrcSymbs);

    int minESI = internal_constants::ESI_min;
    int maxESI = internal_constants::ESI_max;
    int totalSymbs = 1 + maxESI - minESI;

    return totalSymbs - numSrcSymbs;
}

uint64_t parameter_checker::_max_allowed_data_length(uint16_t T)
{
    return std::min(internal_constants::F_max,
                    (uint64_t)(T * internal_constants::Kt_max));
}

uint16_t parameter_checker::_min_allowed_symbol_size(uint64_t F)
{
    return std::max((uint16_t)internal_constants::T_min,
                    (uint16_t)(extra_math::ceil_div(F, internal_constants::Kt_max)));
}

uint16_t parameter_checker::_min_allowed_num_source_blocks(uint16_t Kt)
{
    return std::max(internal_constants::Z_min, (uint16_t)extra_math::ceil_div(Kt,
                    internal_constants::K_max));
}

uint16_t parameter_checker::_max_allowed_num_source_blocks(uint16_t Kt)
{
    return std::min(internal_constants::Z_max, Kt);
}

uint16_t parameter_checker::_max_allowed_interleaver_length(uint16_t T)
{
    return std::min(internal_constants::N_max,
                    (uint16_t)(T / internal_constants::Al));
}

uint64_t parameter_checker::_min_allowed_decoding_block_size(uint64_t F,
        uint16_t T)
{
    int Kt = internal_functions::get_total_symbols(F, T);

    int Kprime = std::max((uint16_t)internal_constants::K_prime_min,
                          (uint16_t)extra_math::ceil_div(Kt, internal_constants::Z_max));

    return internal_functions::min_WS(Kprime, T, internal_constants::Al,
                                      internal_functions::top_interleaver_length(T));
}

uint64_t parameter_checker::_max_allowed_data_length(uint16_t T, uint64_t WS)
{
    long boundFromT = _max_allowed_data_length(T);

    int KL = internal_functions::KL(WS, T, internal_constants::Al,
                                    internal_functions::top_interleaver_length(T));
    long boundFromWS = (long)internal_constants::Z_max * KL * T;

    return std::min(boundFromT, boundFromWS);
}

bool parameter_checker::_are_data_length_and_symbol_size_out_of_bounds(
    uint64_t F,
    uint16_t T)
{
    return internal_functions::get_possible_total_symbols(F,
            T) > internal_constants::Kt_max;
}

bool parameter_checker::_are_data_length_and_payload_length_out_of_bounds(
    uint64_t F,
    uint16_t P)
{
    return _are_data_length_and_symbol_size_out_of_bounds(F, P);
}

void parameter_checker::_check_data_length_out_of_bounds(uint64_t F)
{
    if (is_data_length_out_of_bounds(F)) {
        throw std::invalid_argument("source data length is out of bounds");
    }
}

void parameter_checker::_check_symbol_size_out_of_bounds(uint16_t T)
{
    if (is_symbol_size_out_of_bounds(T)) {
        throw std::invalid_argument("symbol size is out of bounds");
    }
}

void parameter_checker::_check_data_length_and_symbol_size_out_of_bounds(
    uint64_t F,
    uint16_t T)
{
    if (_are_data_length_and_symbol_size_out_of_bounds(F, T)) {
        throw std::invalid_argument("source data length and symbol size are out of bounds in unison");
    }
}

void parameter_checker::_check_num_source_blocks_out_of_bounds(uint8_t Z)
{
    if (is_num_source_blocks_out_of_bounds(Z)) {
        throw std::invalid_argument("number of source blocks is out of bounds");
    }
}

void parameter_checker::_check_payload_length_out_of_bounds(uint16_t P)
{
    if (is_payload_length_out_of_bounds(P)) {
        throw std::invalid_argument("payload length is out of bounds");
    }
}

void parameter_checker::_check_data_length_and_payload_length_out_of_bounds(
    uint64_t F, uint16_t P)
{
    if (_are_data_length_and_payload_length_out_of_bounds(F, P)) {
        throw std::invalid_argument("source data length and payload length are out of bounds in unison");
    }
}

void parameter_checker::_check_decoding_block_size_out_of_bounds(uint64_t WS)
{
    if (WS < min_decoding_block_size()) {
        throw std::invalid_argument("maximum decoding block size is out of bounds");
    }
}

void parameter_checker::_check_num_source_symbols_per_block_out_of_bounds(
    uint16_t K)
{
    if (is_num_source_symbols_per_block_out_of_bounds(K)) {
        throw std::invalid_argument("number of source symbols per block is out of bounds");
    }
}
