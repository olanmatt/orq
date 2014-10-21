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

#include <parameters/parameter_io.h>

int ParameterIO::data_length_shift()
{
    return (1 + sizeof(unsigned short)) * sizeof(uint8_t) *
           8;  // shift by (1 + 2) octets
}

uint64_t ParameterIO::extract_data_length(uint64_t commonFecOTI)
{
    return commonFecOTI >> data_length_shift();
}

uint16_t ParameterIO::extract_symbol_size(uint64_t commonFecOTI)
{
    return (uint16_t)commonFecOTI;
}

int ParameterIO::num_source_blocks_shift()
{
    return (sizeof(uint16_t) + 1) * sizeof(uint8_t) * 8;  // shift by (2 + 1) octets
}

uint8_t ParameterIO::extract_num_source_blocks(uint32_t schemeSpecFecOTI)
{
    return (uint8_t)(schemeSpecFecOTI >> num_source_blocks_shift());
}

int ParameterIO::interleaver_length_shift()
{
    return 1 * sizeof(uint8_t) * 8;  // shift by 1 octet
}

uint16_t ParameterIO::extract_interleaver_length(uint32_t schemeSpecFecOTI)
{
    return (uint16_t)(schemeSpecFecOTI >> interleaver_length_shift());
}

uint8_t ParameterIO::extract_symbol_alignment(uint32_t schemeSpecFecOTI)
{
    return (uint8_t)schemeSpecFecOTI;
}

int ParameterIO::source_block_number_shift()
{
    return internal_constants::ESI_num_bytes * sizeof(uint8_t) * 8;
}

uint8_t ParameterIO::extract_source_block_number(uint32_t fecPayloadID)
{
    return (uint8_t)(fecPayloadID >> source_block_number_shift());
}

uint32_t ParameterIO::extract_encoding_symbol_id(uint32_t fecPayloadID)
{
    return fecPayloadID;
}

uint64_t ParameterIO::build_common_fec_oti(uint64_t dataLen,
        uint16_t symbolSize)
{
    return (dataLen << data_length_shift()) | symbolSize;
}

uint64_t ParameterIO::canonicalize_common_fec_oti(uint64_t commonFecOTI)
{
    return commonFecOTI & internal_constants::common_oti_reserved_inverse_mask;
}

uint32_t ParameterIO::build_scheme_spec_fec_oti(uint8_t numSrcBs,
        uint16_t interLen, uint8_t sAlign)
{
    return (numSrcBs << num_source_blocks_shift()) | (interLen <<
            interleaver_length_shift()) | sAlign;
}

uint32_t ParameterIO::build_fec_payload_id(uint8_t sbn, uint32_t esi)
{
    return (sbn << source_block_number_shift()) | esi;
}
