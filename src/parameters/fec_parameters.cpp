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

#include <parameters/fec_parameters.h>

fec_parameters
fec_parameters::new_parameters(uint64_t data_length,
                               uint16_t symbol_size,
                               uint8_t num_source_blocks)
{
    return new_parameters(data_length, symbol_size, num_source_blocks, 1);
}

fec_parameters
fec_parameters::new_parameters(uint64_t data_length,
                               uint16_t symbol_size,
                               uint8_t num_source_blocks,
                               uint16_t interleaver_length)
{
    uint64_t F = data_length;
    uint16_t T = symbol_size;
    uint8_t Z = num_source_blocks;
    uint16_t N = interleaver_length;
    uint8_t Al = internal_constants::Al;

    if (parameter_checker::are_valid_fec_parameters(F, T, Z, N)) {
        return new_local_instance(F, T, Z, N, Al);
    } else {
        // TODO(olanmatt): Add more exception specificity.
        throw std::invalid_argument("invalid FECParameter argument");
    }
}

fec_parameters
fec_parameters::derive_parameters(uint64_t data_length,
                                  uint16_t payload_length,
                                  uint64_t max_db_mem)
{
    uint64_t F = data_length;
    uint16_t P = payload_length;
    uint64_t WS = max_db_mem;
    uint8_t Al = internal_constants::Al;

    if (parameter_checker::are_valid_deriver_parameters(F, P, WS)) {
        uint16_t T = P;

        uint16_t Kt = internal_functions::get_total_symbols(F, T);
        uint16_t topN = internal_functions::top_interleaver_length(T);

        uint8_t Z = derive_Z(Kt, WS, T, Al, topN);
        uint16_t N = derive_N(Kt, Z, WS, T, Al, topN);

        return new_local_instance(F, T, Z, N, Al);
    } else {
        // TODO(olanmatt): Add more exception specificity.
        throw std::invalid_argument("invalid FECParameter argument");
    }
}

uint8_t
fec_parameters::derive_Z(uint16_t Kt,
                         uint64_t WS,
                         uint16_t T,
                         uint8_t Al,
                         uint16_t topN)
{
    int Kl = internal_functions::KL(WS, T, Al, topN);
    return extra_math::ceil_div(Kt, Kl);  // Z = ceil(Kt/KL(N_max))
}

int
fec_parameters::derive_N(uint16_t Kt,
                         uint8_t Z,
                         uint64_t WS,
                         uint16_t T,
                         uint8_t Al,
                         uint16_t topN)
{
    // N is the minimum n=1, ..., N_max such that ceil(Kt/Z) <= KL(n)
    int topK = extra_math::ceil_div(Kt, Z);
    for (int n = topN; n >= 1; n--) {
        if (topK <= internal_functions::KL(WS, T, Al, n)) {
            return n;
        }
    }

    throw std::runtime_error("must never be thrown");
}

fec_parameters
fec_parameters::new_local_instance(uint64_t F,
                                   uint16_t T,
                                   uint8_t Z,
                                   uint16_t N,
                                   uint8_t Al)
{
    uint64_t common_fec_oti = parameter_io::build_common_fec_oti(F, T);
    uint32_t scheme_spec_fec_oti = parameter_io::build_scheme_spec_fec_oti(Z, N,
                                   Al);
    return fec_parameters(common_fec_oti, scheme_spec_fec_oti);
}

fec_parameters::fec_parameters(uint64_t common_fec_oti,
                               uint32_t scheme_spec_fec_oti)
{
    common_fec_oti_ = common_fec_oti;
    scheme_spec_fec_oti_ = scheme_spec_fec_oti;
}

uint64_t
fec_parameters::data_length(void)
{
    return parameter_io::extract_data_length(common_fec_oti_);
}

uint16_t
fec_parameters::symbol_size(void)
{
    return parameter_io::extract_symbol_size(common_fec_oti_);
}

uint8_t
fec_parameters::num_source_blocks(void)
{
    return parameter_io::extract_num_source_blocks(scheme_spec_fec_oti_);
}

uint16_t
fec_parameters::interleaver_length(void)
{
    return parameter_io::extract_interleaver_length(scheme_spec_fec_oti_);
}

uint8_t
fec_parameters::symbol_alignment(void)
{
    return parameter_io::extract_symbol_alignment(scheme_spec_fec_oti_);
}

uint16_t
fec_parameters::total_symbols(void)
{
    return internal_functions::get_total_symbols(data_length(), symbol_size());
}
