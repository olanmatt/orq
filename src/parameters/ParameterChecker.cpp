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

uint64_t ParameterChecker::minDataLength()
{
    return internal_constants::F_min;
}

uint64_t ParameterChecker::maxDataLength()
{
    return internal_constants::F_max;
}

bool ParameterChecker::isDataLengthOutOfBounds(uint64_t dataLen)
{
    return !(minDataLength() <= dataLen && dataLen <= maxDataLength());
}

uint64_t ParameterChecker::maxAllowedDataLength(uint16_t symbSize)
{
    _checkSymbolSizeOutOfBounds(symbSize);
    return _maxAllowedDataLength(symbSize);
}

uint16_t ParameterChecker::minSymbolSize()
{
    return internal_constants::T_min;
}

uint16_t ParameterChecker::maxSymbolSize()
{
    return internal_constants::T_max;
}

bool ParameterChecker::isSymbolSizeOutOfBounds(uint16_t symbSize)
{
    return !(minSymbolSize() <= symbSize && symbSize <= maxSymbolSize());
}

uint16_t ParameterChecker::minAllowedSymbolSize(uint64_t dataLen)
{
    _checkDataLengthOutOfBounds(dataLen);
    return _minAllowedSymbolSize(dataLen);
}

uint16_t ParameterChecker::minNumSourceBlocks()
{
    return internal_constants::Z_min;
}

uint16_t ParameterChecker::maxNumSourceBlocks()
{
    return internal_constants::Z_max;
}

bool ParameterChecker::isNumSourceBlocksOutOfBounds(uint8_t numSrcBs)
{
    return !(minNumSourceBlocks() <= numSrcBs && numSrcBs <= maxNumSourceBlocks());
}

uint8_t ParameterChecker::minAllowedNumSourceBlocks(uint64_t dataLen, uint16_t symbSize)
{
    _checkDataLengthOutOfBounds(dataLen);
    _checkSymbolSizeOutOfBounds(symbSize);
    _checkDataLengthAndSymbolSizeOutOfBounds(dataLen, symbSize);

    uint32_t Kt = internal_functions::get_total_symbols(dataLen, symbSize);
    return _minAllowedNumSourceBlocks(Kt);
}

uint8_t ParameterChecker::maxAllowedNumSourceBlocks(uint64_t dataLen, uint16_t symbSize)
{
    _checkDataLengthOutOfBounds(dataLen);
    _checkSymbolSizeOutOfBounds(symbSize);
    _checkDataLengthAndSymbolSizeOutOfBounds(dataLen, symbSize);

    uint16_t Kt = internal_functions::get_total_symbols(dataLen, symbSize);
    return _maxAllowedNumSourceBlocks(Kt);
}

uint16_t ParameterChecker::minInterleaverLength()
{
    return internal_constants::N_min;
}

uint16_t ParameterChecker::maxInterleaverLength()
{
    return internal_constants::N_max;
}

bool ParameterChecker::isInterleaverLengthOutOfBounds(uint16_t interLen)
{
    return !(minInterleaverLength() <= interLen && interLen <= maxInterleaverLength());
}

uint16_t ParameterChecker::maxAllowedInterleaverLength(uint16_t symbSize)
{
    _checkSymbolSizeOutOfBounds(symbSize);
    return _maxAllowedInterleaverLength(symbSize);
}

uint8_t ParameterChecker::symbolAlignmentValue()
{
    return internal_constants::Al;
}

bool ParameterChecker::areValidFECParameters(uint64_t dataLen, uint16_t symbSize, uint8_t numSrcBs, uint16_t interLen)
{
    uint64_t F = dataLen;
    uint16_t T = symbSize;
    uint8_t Z = numSrcBs;
    uint16_t N = interLen;

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

    int Kt = internal_functions::get_total_symbols(F, T);
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

uint16_t ParameterChecker::minPayloadLength()
{
    return minSymbolSize();
}

uint16_t ParameterChecker::maxPayloadLength()
{
    return maxSymbolSize();
}

bool ParameterChecker::isPayloadLengthOutOfBounds(uint16_t payLen)
{
    return !(minPayloadLength() <= payLen && payLen <= maxPayloadLength());
}

uint16_t ParameterChecker::minAllowedPayloadLength(uint64_t dataLen)
{
    return minAllowedSymbolSize(dataLen);
}

uint64_t ParameterChecker::minDecodingBlockSize()
{
    return _minAllowedDecodingBlockSize(minDataLength(), minSymbolSize());
}

uint64_t ParameterChecker::minAllowedDecodingBlockSize(uint64_t dataLen, uint16_t payLen)
{
    _checkDataLengthOutOfBounds(dataLen);
    _checkPayloadLengthOutOfBounds(payLen);
    _checkDataLengthAndPayloadLengthOutOfBounds(dataLen, payLen);

    return _minAllowedDecodingBlockSize(dataLen, payLen);
}

uint64_t ParameterChecker::maxAllowedDataLength(uint16_t payLen, uint64_t maxDBMem)
{
    _checkPayloadLengthOutOfBounds(payLen);
    _checkDecodingBlockSizeOutOfBounds(maxDBMem);
    if (maxDBMem < payLen) {
        throw std::invalid_argument("maximum decoding block size must be at least equal to the payload length");
    }

    return _maxAllowedDataLength(payLen, maxDBMem);
}

bool ParameterChecker::areValidDeriverParameters(uint64_t dataLen, uint16_t payLen, uint64_t maxDBMem)
{
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

uint8_t ParameterChecker::minSourceBlockNumber()
{
    return internal_constants::SBN_min;
}

uint8_t ParameterChecker::maxSourceBlockNumber()
{
    return internal_constants::SBN_max;
}

bool ParameterChecker::isSourceBlockNumberOutOfBounds(uint8_t sbn)
{
    return !(minSourceBlockNumber() <= sbn && sbn <= maxSourceBlockNumber());
}

uint32_t ParameterChecker::minEncodingSymbolID()
{
    return internal_constants::ESI_min;
}

uint32_t ParameterChecker::maxEncodingSymbolID()
{
    return internal_constants::ESI_max;
}

bool ParameterChecker::isEncodingSymbolIDOutOfBounds(uint32_t esi)
{
    return !(minEncodingSymbolID() <= esi && esi <= maxEncodingSymbolID());
}

bool ParameterChecker::isValidFECPayloadID(uint8_t sbn, uint32_t esi, uint8_t numSrcBs)
{
    _checkNumSourceBlocksOutOfBounds(numSrcBs);

    if (sbn < internal_constants::SBN_min || sbn >= numSrcBs) {
        return false;
    }
    if (isEncodingSymbolIDOutOfBounds(esi)) {
        return false;
    }

    return true;
}

uint16_t ParameterChecker::minNumSourceSymbolsPerBlock()
{
    return internal_constants::K_min;
}

uint16_t ParameterChecker::maxNumSourceSymbolsPerBlock()
{
    return internal_constants::K_max;
}

bool ParameterChecker::isNumSourceSymbolsPerBlockOutOfBounds(uint16_t numSrcSymbs)
{
    return !(minNumSourceSymbolsPerBlock() <= numSrcSymbs && numSrcSymbs <= maxNumSourceSymbolsPerBlock());
}

uint32_t ParameterChecker::numRepairSymbolsPerBlock(uint16_t numSrcSymbs)
{
    _checkNumSourceSymbolsPerBlockOutOfBounds(numSrcSymbs);

    int minESI = minEncodingSymbolID();
    int maxESI = maxEncodingSymbolID();
    int totalSymbs = 1 + maxESI - minESI;

    return totalSymbs - numSrcSymbs;
}

uint64_t ParameterChecker::_maxAllowedDataLength(uint16_t T)
{
    return std::min(internal_constants::F_max, (uint64_t)(T * internal_constants::Kt_max));
}

uint16_t ParameterChecker::_minAllowedSymbolSize(uint64_t F)
{
    return std::max((uint16_t)internal_constants::T_min, (uint16_t)(extra_math::ceil_div(F, internal_constants::Kt_max)));
}

uint16_t ParameterChecker::_minAllowedNumSourceBlocks(uint16_t Kt)
{
    return std::max(internal_constants::Z_min, (uint16_t)extra_math::ceil_div(Kt, internal_constants::K_max));
}

uint16_t ParameterChecker::_maxAllowedNumSourceBlocks(uint16_t Kt)
{
    return std::min(internal_constants::Z_max, Kt);
}

uint16_t ParameterChecker::_maxAllowedInterleaverLength(uint16_t T)
{
    return std::min(internal_constants::N_max, (uint16_t)(T / internal_constants::Al));
}

uint64_t ParameterChecker::_minAllowedDecodingBlockSize(uint64_t F, uint16_t T)
{
    int Kt = internal_functions::get_total_symbols(F, T);

    int Kprime = std::max((uint16_t)internal_constants::K_prime_min, (uint16_t)extra_math::ceil_div(Kt, internal_constants::Z_max));

    return internal_functions::min_WS(Kprime, T, internal_constants::Al, internal_functions::top_interleaver_length(T));
}

uint64_t ParameterChecker::_maxAllowedDataLength(uint16_t T, uint64_t WS)
{
    long boundFromT = _maxAllowedDataLength(T);

    int KL = internal_functions::KL(WS, T, internal_constants::Al, internal_functions::top_interleaver_length(T));
    long boundFromWS = (long)internal_constants::Z_max * KL * T;

    return std::min(boundFromT, boundFromWS);
}

bool ParameterChecker::_areDataLengthAndSymbolSizeOutOfBounds(uint64_t F, uint16_t T)
{
    return internal_functions::get_possible_total_symbols(F, T) > internal_constants::Kt_max;
}

bool ParameterChecker::_areDataLengthAndPayloadLengthOutOfBounds(uint64_t F, uint16_t P)
{
    return _areDataLengthAndSymbolSizeOutOfBounds(F, P);
}

void ParameterChecker::_checkDataLengthOutOfBounds(uint64_t F)
{
    if (isDataLengthOutOfBounds(F)) {
        throw std::invalid_argument("source data length is out of bounds");
    }
}

void ParameterChecker::_checkSymbolSizeOutOfBounds(uint16_t T)
{
    if (isSymbolSizeOutOfBounds(T)) {
        throw std::invalid_argument("symbol size is out of bounds");
    }
}

void ParameterChecker::_checkDataLengthAndSymbolSizeOutOfBounds(uint64_t F, uint16_t T)
{
    if (_areDataLengthAndSymbolSizeOutOfBounds(F, T)) {
        throw std::invalid_argument("source data length and symbol size are out of bounds in unison");
    }
}

void ParameterChecker::_checkNumSourceBlocksOutOfBounds(uint8_t Z)
{
    if (isNumSourceBlocksOutOfBounds(Z)) {
        throw std::invalid_argument("number of source blocks is out of bounds");
    }
}

void ParameterChecker::_checkPayloadLengthOutOfBounds(uint16_t P)
{
    if (isPayloadLengthOutOfBounds(P)) {
        throw std::invalid_argument("payload length is out of bounds");
    }
}

void ParameterChecker::_checkDataLengthAndPayloadLengthOutOfBounds(uint64_t F, uint16_t P)
{
    if (_areDataLengthAndPayloadLengthOutOfBounds(F, P)) {
        throw std::invalid_argument("source data length and payload length are out of bounds in unison");
    }
}

void ParameterChecker::_checkDecodingBlockSizeOutOfBounds(uint64_t WS)
{
    if (WS < minDecodingBlockSize()) {
        throw std::invalid_argument("maximum decoding block size is out of bounds");
    }
}

void ParameterChecker::_checkNumSourceSymbolsPerBlockOutOfBounds(uint16_t K)
{
    if (isNumSourceSymbolsPerBlockOutOfBounds(K)) {
        throw std::invalid_argument("number of source symbols per block is out of bounds");
    }
}
