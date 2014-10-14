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
#include <util/ExtraMath.h>

class ParameterChecker {
	
	public:
	static uint64_t minDataLength();
	static uint64_t maxDataLength();
	static bool isDataLengthOutOfBounds(uint64_t dataLen);
	static long maxAllowedDataLength(int symbSize);
	static uint16_t minSymbolSize();
	static uint16_t maxSymbolSize();
	static bool isSymbolSizeOutOfBounds(uint16_t symbSize);
	static int minAllowedSymbolSize(long dataLen);
	static int minNumSourceBlocks();
	static int maxNumSourceBlocks();
	static bool isNumSourceBlocksOutOfBounds(int numSrcBs);
	static int minAllowedNumSourceBlocks(long dataLen, int symbSize);
	static int maxAllowedNumSourceBlocks(long dataLen, int symbSize);
	static int minInterleaverLength();
	static int maxInterleaverLength();
	static bool isInterleaverLengthOutOfBounds(int interLen);
	static int maxAllowedInterleaverLength(int symbSize);
	static int symbolAlignmentValue();
	static bool areValidFECParameters(long dataLen, int symbSize, int numSrcBs, int interLen);
	static int minPayloadLength();
	static int maxPayloadLength();
	static bool isPayloadLengthOutOfBounds(int payLen);
	static int minAllowedPayloadLength(long dataLen);
	static long minDecodingBlockSize();
	static long minAllowedDecodingBlockSize(long dataLen, int payLen);
	static long maxAllowedDataLength(int payLen, long maxDBMem);
	static bool areValidDeriverParameters(long dataLen, int payLen, long maxDBMem);
	static int minSourceBlockNumber();
	static int maxSourceBlockNumber();
	static bool isSourceBlockNumberOutOfBounds(int sbn);
	static int minEncodingSymbolID();
	static int maxEncodingSymbolID();
	static bool isEncodingSymbolIDOutOfBounds(int esi);
	static bool isValidFECPayloadID(int sbn, int esi, int numSrcBs);
	static int minNumSourceSymbolsPerBlock();
	static int maxNumSourceSymbolsPerBlock();
	static bool isNumSourceSymbolsPerBlockOutOfBounds(int numSrcSymbs);
	static int numRepairSymbolsPerBlock(int numSrcSymbs);

	private:
	static long _maxAllowedDataLength(int T);
	static int _minAllowedSymbolSize(long F);
	static int _minAllowedNumSourceBlocks(int Kt);
	static int _maxAllowedNumSourceBlocks(int Kt);
	static int _maxAllowedInterleaverLength(int T);
	static long _minAllowedDecodingBlockSize(long F, int T);
	static long _maxAllowedDataLength(int T, long WS);
	static bool _areDataLengthAndSymbolSizeOutOfBounds(long F, int T);
	static bool _areDataLengthAndPayloadLengthOutOfBounds(long F, int P);
	static void _checkDataLengthOutOfBounds(long F);
	static void _checkSymbolSizeOutOfBounds(int T);
	static void _checkDataLengthAndSymbolSizeOutOfBounds(long F, int T);
	static void _checkNumSourceBlocksOutOfBounds(int Z);
	static void _checkPayloadLengthOutOfBounds(int P);
	static void _checkDataLengthAndPayloadLengthOutOfBounds(long F, int P);
	static void _checkDecodingBlockSizeOutOfBounds(long WS);
	static void _checkNumSourceSymbolsPerBlockOutOfBounds(int K);
};

#endif
