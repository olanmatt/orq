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

#ifndef PARAMETERCHECKER_H
#define PARAMETERCHECKER_H

#include <algorithm>
#include <parameters/InternalConstants.h>
#include <parameters/InternalFunctions.h>
#include <util/extra_math.h>

class ParameterChecker {

	public:
	static uint64_t minDataLength();
	static uint64_t maxDataLength();
	static bool isDataLengthOutOfBounds(uint64_t dataLen);
	static uint64_t maxAllowedDataLength(uint16_t symbSize);
	static uint16_t minSymbolSize();
	static uint16_t maxSymbolSize();
	static bool isSymbolSizeOutOfBounds(uint16_t symbSize);
	static uint16_t minAllowedSymbolSize(uint64_t dataLen);
	static uint16_t minNumSourceBlocks();
	static uint16_t maxNumSourceBlocks();
	static bool isNumSourceBlocksOutOfBounds(uint8_t numSrcBs);
	static uint8_t minAllowedNumSourceBlocks(uint64_t dataLen, uint16_t symbSize);
	static uint8_t maxAllowedNumSourceBlocks(uint64_t dataLen, uint16_t symbSize);
	static uint16_t minInterleaverLength();
	static uint16_t maxInterleaverLength();
	static bool isInterleaverLengthOutOfBounds(uint16_t interLen);
	static uint16_t maxAllowedInterleaverLength(uint16_t symbSize);
	static uint8_t symbolAlignmentValue();
	static bool areValidFECParameters(uint64_t dataLen, uint16_t symbSize, uint8_t numSrcBs, uint16_t interLen);
	static uint16_t minPayloadLength();
	static uint16_t maxPayloadLength();
	static bool isPayloadLengthOutOfBounds(uint16_t payLen);
	static uint16_t minAllowedPayloadLength(uint64_t dataLen);
	static uint64_t minDecodingBlockSize();
	static uint64_t minAllowedDecodingBlockSize(uint64_t dataLen, uint16_t payLen);
	static uint64_t maxAllowedDataLength(uint16_t payLen, uint64_t maxDBMem);
	static bool areValidDeriverParameters(uint64_t dataLen, uint16_t payLen, uint64_t maxDBMem);
	static uint8_t minSourceBlockNumber();
	static uint8_t maxSourceBlockNumber();
	static bool isSourceBlockNumberOutOfBounds(uint8_t sbn);
	static uint32_t minEncodingSymbolID();
	static uint32_t maxEncodingSymbolID();
	static bool isEncodingSymbolIDOutOfBounds(uint32_t esi);
	static bool isValidFECPayloadID(uint8_t sbn, uint32_t esi, uint8_t numSrcBs);
	static uint16_t minNumSourceSymbolsPerBlock();
	static uint16_t maxNumSourceSymbolsPerBlock();
	static bool isNumSourceSymbolsPerBlockOutOfBounds(uint16_t numSrcSymbs);
	static uint32_t numRepairSymbolsPerBlock(uint16_t numSrcSymbs);

	private:
	static uint64_t _maxAllowedDataLength(uint16_t T);
	static uint16_t _minAllowedSymbolSize(uint64_t F);
	static uint16_t _minAllowedNumSourceBlocks(uint16_t Kt);
	static uint16_t _maxAllowedNumSourceBlocks(uint16_t Kt);
	static uint16_t _maxAllowedInterleaverLength(uint16_t T);
	static uint64_t _minAllowedDecodingBlockSize(uint64_t F, uint16_t T);
	static uint64_t _maxAllowedDataLength(uint16_t T, uint64_t WS);
	static bool _areDataLengthAndSymbolSizeOutOfBounds(uint64_t F, uint16_t T);
	static bool _areDataLengthAndPayloadLengthOutOfBounds(uint64_t F, uint16_t P);
	static void _checkDataLengthOutOfBounds(uint64_t F);
	static void _checkSymbolSizeOutOfBounds(uint16_t T);
	static void _checkDataLengthAndSymbolSizeOutOfBounds(uint64_t F, uint16_t T);
	static void _checkNumSourceBlocksOutOfBounds(uint8_t Z);
	static void _checkPayloadLengthOutOfBounds(uint16_t P);
	static void _checkDataLengthAndPayloadLengthOutOfBounds(uint64_t F, uint16_t P);
	static void _checkDecodingBlockSizeOutOfBounds(uint64_t WS);
	static void _checkNumSourceSymbolsPerBlockOutOfBounds(uint16_t K);
};

#endif
