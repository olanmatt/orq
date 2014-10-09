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

#include <parameters/ParameterIO.h>

int ParameterIO::dataLengthShift() {

	return (1 + sizeof(unsigned short)) * sizeof(uint8_t) * 8; // shift by (1 + 2) octets
}

uint64_t ParameterIO::extractDataLength(uint64_t commonFecOTI) {

	return commonFecOTI >> dataLengthShift();
}

uint16_t ParameterIO::extractSymbolSize(uint64_t commonFecOTI) {

	return (uint16_t)commonFecOTI;
}

int ParameterIO::numSourceBlocksShift() {

	return (sizeof(uint16_t) + 1) * sizeof(uint8_t) * 8; // shift by (2 + 1) octets
}

uint8_t ParameterIO::extractNumSourceBlocks(uint32_t schemeSpecFecOTI) {

	return (uint8_t)(schemeSpecFecOTI >> numSourceBlocksShift());
}

int ParameterIO::interleaverLengthShift() {

	return 1 * sizeof(uint8_t) * 8; // shift by 1 octet
}

uint16_t ParameterIO::extractInterleaverLength(uint32_t schemeSpecFecOTI) {

	return (uint16_t)(schemeSpecFecOTI >> interleaverLengthShift());
}

uint8_t ParameterIO::extractSymbolAlignment(uint32_t schemeSpecFecOTI) {

	return (uint8_t)schemeSpecFecOTI;
}

int ParameterIO::sourceBlockNumberShift() {

	return InternalConstants::ESI_num_bytes * sizeof(uint8_t) * 8;
}

uint8_t ParameterIO::extractSourceBlockNumber(uint32_t fecPayloadID) {

	return (uint8_t)(fecPayloadID >> sourceBlockNumberShift());
}

uint32_t ParameterIO::extractEncodingSymbolID(uint32_t fecPayloadID) {

	return fecPayloadID;
}

uint64_t ParameterIO::buildCommonFecOTI(uint64_t dataLen, uint16_t symbolSize) {

	return (dataLen << dataLengthShift()) | symbolSize;
}

uint64_t ParameterIO::canonicalizeCommonFecOTI(uint64_t commonFecOTI) {

	return commonFecOTI & InternalConstants::common_OTI_reserved_inverse_mask;
}

uint32_t ParameterIO::buildSchemeSpecFecOTI(uint8_t numSrcBs, uint16_t interLen, uint8_t sAlign) {

	return (numSrcBs << numSourceBlocksShift()) | (interLen << interleaverLengthShift()) | sAlign;
}

uint32_t ParameterIO::buildFECpayloadID(uint8_t sbn, uint32_t esi) {

	return (sbn << sourceBlockNumberShift()) | esi;
}
