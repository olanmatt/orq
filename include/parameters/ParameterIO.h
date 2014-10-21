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

#ifndef PARAMETERIO_H
#define PARAMETERIO_H

#include <parameters/internal_constants.h>
#include <stdint.h>

class ParameterIO {

	public:
	static uint64_t extractDataLength(uint64_t commonFecOTI);
	static uint16_t extractSymbolSize(uint64_t commonFecOTI);
	static uint8_t extractNumSourceBlocks(uint32_t schemeSpecFecOTI);
	static uint16_t extractInterleaverLength(uint32_t schemeSpecFecOTI);
	static uint8_t extractSymbolAlignment(uint32_t schemeSpecFecOTI);
	static uint8_t extractSourceBlockNumber(uint32_t fecPayloadID);
	static uint32_t extractEncodingSymbolID(uint32_t fecPayloadID);
	static uint64_t buildCommonFecOTI(uint64_t dataLen, uint16_t symbolSize);
	static uint64_t canonicalizeCommonFecOTI(uint64_t commonFecOTI);
	static uint32_t buildSchemeSpecFecOTI(uint8_t numSrcBs, uint16_t interLen, uint8_t sAlign);
	static uint32_t buildFECpayloadID(uint8_t sbn, uint32_t esi);

	private:
	static int dataLengthShift();
	static int numSourceBlocksShift();
	static int interleaverLengthShift();
	static int sourceBlockNumberShift();
};

#endif
