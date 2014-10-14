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

#include <parameters/ParameterChecker.h>

uint64_t ParameterChecker::minDataLength() {

	return InternalConstants::F_min;
}

uint64_t ParameterChecker::maxDataLength() {

	return InternalConstants::F_max;
}

bool ParameterChecker::isDataLengthOutOfBounds(uint64_t dataLen) {

	return !(minDataLength() <= dataLen && dataLen <= maxDataLength());
}

long ParameterChecker::maxAllowedDataLength(int symbSize) {

	_checkSymbolSizeOutOfBounds(symbSize);
	return _maxAllowedDataLength(symbSize);
}

uint16_t ParameterChecker::minSymbolSize() {

	return InternalConstants::T_min;
}

uint16_t ParameterChecker::maxSymbolSize() {

	return InternalConstants::T_max;
}

bool ParameterChecker::isSymbolSizeOutOfBounds(uint16_t symbSize) {

	return !(minSymbolSize() <= symbSize && symbSize <= maxSymbolSize());
}

int ParameterChecker::minAllowedSymbolSize(long dataLen) {

	_checkDataLengthOutOfBounds(dataLen);
	return _minAllowedSymbolSize(dataLen);
}

int ParameterChecker::minNumSourceBlocks() {

	return InternalConstants::Z_min;
}

int ParameterChecker::maxNumSourceBlocks() {

	return InternalConstants::Z_max;
}

bool ParameterChecker::isNumSourceBlocksOutOfBounds(int numSrcBs) {

	return !(minNumSourceBlocks() <= numSrcBs && numSrcBs <= maxNumSourceBlocks());
}

int ParameterChecker::minAllowedNumSourceBlocks(long dataLen, int symbSize) {

	_checkDataLengthOutOfBounds(dataLen);
	_checkSymbolSizeOutOfBounds(symbSize);
	_checkDataLengthAndSymbolSizeOutOfBounds(dataLen, symbSize);

	int Kt = InternalFunctions::getTotalSymbols(dataLen, symbSize);
	return _minAllowedNumSourceBlocks(Kt);
}

int ParameterChecker::maxAllowedNumSourceBlocks(long dataLen, int symbSize) {

	_checkDataLengthOutOfBounds(dataLen);
	_checkSymbolSizeOutOfBounds(symbSize);
	_checkDataLengthAndSymbolSizeOutOfBounds(dataLen, symbSize);

	int Kt = InternalFunctions::getTotalSymbols(dataLen, symbSize);
	return _maxAllowedNumSourceBlocks(Kt);
}

int ParameterChecker::minInterleaverLength() {

	return InternalConstants::N_min;
}

int ParameterChecker::maxInterleaverLength() {

	return InternalConstants::N_max;
}

bool ParameterChecker::isInterleaverLengthOutOfBounds(int interLen) {

	return !(minInterleaverLength() <= interLen && interLen <= maxInterleaverLength());
}

int ParameterChecker::maxAllowedInterleaverLength(int symbSize) {

	_checkSymbolSizeOutOfBounds(symbSize);
	return _maxAllowedInterleaverLength(symbSize);
}

int ParameterChecker::symbolAlignmentValue() {
	
	return InternalConstants::Al;
}

bool ParameterChecker::areValidFECParameters(long dataLen, int symbSize, int numSrcBs, int interLen) {

	long F = dataLen;
	int T = symbSize;
	int Z = numSrcBs;
	int N = interLen;

	if (isDataLengthOutOfBounds(F)) {
		return false;
	}
	if (isSymbolSizeOutOfBounds(T)) {
		return false;
	}
	if (isNumSourceBlocksOutOfBounds(Z)) {
		return false;
	}
	if (isInterleaverLengthOutOfBounds(N)) {
		return false;
	}
	
	if (_areDataLengthAndSymbolSizeOutOfBounds(F, T)) {
		return false;
	}

	int Kt = InternalFunctions::getTotalSymbols(F, T);
	int minAllowedZ = _minAllowedNumSourceBlocks(Kt);
	int maxAllowedZ = _maxAllowedNumSourceBlocks(Kt);

	if (Z < minAllowedZ || Z > maxAllowedZ) {
		return false;
	}

	int maxAllowedN = _maxAllowedInterleaverLength(T);

	if (N > maxAllowedN) {
		return false;
	}

	return true;
}

int ParameterChecker::minPayloadLength() {

	return minSymbolSize();
}

int ParameterChecker::maxPayloadLength() {

	return maxSymbolSize();
}

bool ParameterChecker::isPayloadLengthOutOfBounds(int payLen) {

	return !(minPayloadLength() <= payLen && payLen <= maxPayloadLength());
}

int ParameterChecker::minAllowedPayloadLength(long dataLen) {

	return minAllowedSymbolSize(dataLen);
}

long ParameterChecker::minDecodingBlockSize() {

	return _minAllowedDecodingBlockSize(minDataLength(), minSymbolSize());
}

long ParameterChecker::minAllowedDecodingBlockSize(long dataLen, int payLen) {

	_checkDataLengthOutOfBounds(dataLen);
	_checkPayloadLengthOutOfBounds(payLen);
	_checkDataLengthAndPayloadLengthOutOfBounds(dataLen, payLen);

	return _minAllowedDecodingBlockSize(dataLen, payLen);
}

long ParameterChecker::maxAllowedDataLength(int payLen, long maxDBMem) {

	_checkPayloadLengthOutOfBounds(payLen);
	_checkDecodingBlockSizeOutOfBounds(maxDBMem);
	if (maxDBMem < payLen) {
		throw std::invalid_argument("maximum decoding block size must be at least equal to the payload length");
	}

	return _maxAllowedDataLength(payLen, maxDBMem);
}

bool ParameterChecker::areValidDeriverParameters(long dataLen, int payLen, long maxDBMem) {

	long F = dataLen;
	int T = payLen;
	long WS = maxDBMem;

	if (isDataLengthOutOfBounds(F)) {
		return false;
	}
	if (isSymbolSizeOutOfBounds(T)) {
		return false;
	}

	long absolMinWS = minDecodingBlockSize();
	if (WS < absolMinWS) {
		return false;
	}

	int minT = _minAllowedSymbolSize(F);
	if (T < minT) {
		return false;
	}

	long minWS = _minAllowedDecodingBlockSize(F, T);
	if (WS < minWS) {
		return false;
	}

	return true;
}

int ParameterChecker::minSourceBlockNumber() {

	return InternalConstants::SBN_min;
}

int ParameterChecker::maxSourceBlockNumber() {

	return InternalConstants::SBN_max;
}

bool ParameterChecker::isSourceBlockNumberOutOfBounds(int sbn) {

	return !(minSourceBlockNumber() <= sbn && sbn <= maxSourceBlockNumber());
}

int ParameterChecker::minEncodingSymbolID() {

	return InternalConstants::ESI_min;
}

int ParameterChecker::maxEncodingSymbolID() {

	return InternalConstants::ESI_max;
}

bool ParameterChecker::isEncodingSymbolIDOutOfBounds(int esi) {

	return !(minEncodingSymbolID() <= esi && esi <= maxEncodingSymbolID());
}

bool ParameterChecker::isValidFECPayloadID(int sbn, int esi, int numSrcBs) {

	_checkNumSourceBlocksOutOfBounds(numSrcBs);

	if (sbn < InternalConstants::SBN_min || sbn >= numSrcBs) {
		return false;
	}
	if (isEncodingSymbolIDOutOfBounds(esi)) {
		return false;
	}

	return true;
}

int ParameterChecker::minNumSourceSymbolsPerBlock() {

	return InternalConstants::K_min;
}

int ParameterChecker::maxNumSourceSymbolsPerBlock() {

	return InternalConstants::K_max;
}

bool ParameterChecker::isNumSourceSymbolsPerBlockOutOfBounds(int numSrcSymbs) {

	return !(minNumSourceSymbolsPerBlock() <= numSrcSymbs && numSrcSymbs <= maxNumSourceSymbolsPerBlock());
}

int ParameterChecker::numRepairSymbolsPerBlock(int numSrcSymbs) {

	_checkNumSourceSymbolsPerBlockOutOfBounds(numSrcSymbs);

	int minESI = minEncodingSymbolID();
	int maxESI = maxEncodingSymbolID();
	int totalSymbs = 1 + maxESI - minESI;

	return totalSymbs - numSrcSymbs;
}

long ParameterChecker::_maxAllowedDataLength(int T) {

	return std::min(maxDataLength(), (uint64_t)(T * InternalConstants::Kt_max));
}

int ParameterChecker::_minAllowedSymbolSize(long F) {

	return std::max(minSymbolSize(), (uint16_t)(ExtraMath::ceilDiv(F, InternalConstants::Kt_max)));
}

int ParameterChecker::_minAllowedNumSourceBlocks(int Kt) {

	return std::max(minNumSourceBlocks(), ExtraMath::ceilDiv(Kt, InternalConstants::K_max));
}

int ParameterChecker::_maxAllowedNumSourceBlocks(int Kt) {

	return std::min(maxNumSourceBlocks(), Kt);
}

int ParameterChecker::_maxAllowedInterleaverLength(int T) {

	return std::min(maxInterleaverLength(), T / InternalConstants::Al);
}

long ParameterChecker::_minAllowedDecodingBlockSize(long F, int T) {

	int Kt = InternalFunctions::getTotalSymbols(F, T);

	// TODO K_prime_min hardcoded to suppress linker error
	//int Kprime = std::max(InternalConstants::K_prime_min, ExtraMath::ceilDiv(Kt, InternalConstants::Z_max));
	int Kprime = std::max(10, ExtraMath::ceilDiv(Kt, InternalConstants::Z_max));

	return InternalFunctions::minWS(Kprime, T, InternalConstants::Al, InternalFunctions::topInterleaverLength(T));
}

long ParameterChecker::_maxAllowedDataLength(int T, long WS) {

	long boundFromT = _maxAllowedDataLength(T);

	int KL = InternalFunctions::KL(WS, T, InternalConstants::Al, InternalFunctions::topInterleaverLength(T));
	long boundFromWS = (long)InternalConstants::Z_max * KL * T;

	return std::min(boundFromT, boundFromWS);
}

bool ParameterChecker::_areDataLengthAndSymbolSizeOutOfBounds(long F, int T) {

	return InternalFunctions::getPossibleTotalSymbols(F, T) > InternalConstants::Kt_max;
}

bool ParameterChecker::_areDataLengthAndPayloadLengthOutOfBounds(long F, int P) {

	return _areDataLengthAndSymbolSizeOutOfBounds(F, P);
}

void ParameterChecker::_checkDataLengthOutOfBounds(long F) {

	if (isDataLengthOutOfBounds(F)) {
		throw std::invalid_argument("source data length is out of bounds");
	}
}

void ParameterChecker::_checkSymbolSizeOutOfBounds(int T) {

	if (isSymbolSizeOutOfBounds(T)) {
		throw std::invalid_argument("symbol size is out of bounds");
	}
}

void ParameterChecker::_checkDataLengthAndSymbolSizeOutOfBounds(long F, int T) {

	if (_areDataLengthAndSymbolSizeOutOfBounds(F, T)) {
		throw std::invalid_argument("source data length and symbol size are out of bounds in unison");
	}
}

void ParameterChecker::_checkNumSourceBlocksOutOfBounds(int Z) {

	if (isNumSourceBlocksOutOfBounds(Z)) {
		throw std::invalid_argument("number of source blocks is out of bounds");
	}
}

void ParameterChecker::_checkPayloadLengthOutOfBounds(int P) {

	if (isPayloadLengthOutOfBounds(P)) {
		throw std::invalid_argument("payload length is out of bounds");
	}
}

void ParameterChecker::_checkDataLengthAndPayloadLengthOutOfBounds(long F, int P) {

	if (_areDataLengthAndPayloadLengthOutOfBounds(F, P)) {
		throw std::invalid_argument("source data length and payload length are out of bounds in unison");
	}
}

void ParameterChecker::_checkDecodingBlockSizeOutOfBounds(long WS) {

	if (WS < minDecodingBlockSize()) {
		throw std::invalid_argument("maximum decoding block size is out of bounds");
	}
}

void ParameterChecker::_checkNumSourceSymbolsPerBlockOutOfBounds(int K) {

	if (isNumSourceSymbolsPerBlockOutOfBounds(K)) {
		throw std::invalid_argument("number of source symbols per block is out of bounds");
	}
}
