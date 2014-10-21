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

#include <parameters/FECParameters.h>

FECParameters FECParameters::newParameters(uint64_t dataLen, uint16_t symbSize, uint8_t numSrcBs) {

	return newParameters(dataLen, symbSize, numSrcBs, 1);
}

FECParameters FECParameters::newParameters(uint64_t dataLen, uint16_t symbSize, uint8_t numSrcBs, uint16_t interLen) {

	uint64_t F = dataLen; // the transfer length of the object, in octets
	uint16_t T = symbSize; // the symbol size in octets, which MUST be a multiple of Al
	uint8_t Z = numSrcBs; // the number of source blocks
	uint16_t N = interLen; // the number of sub-blocks in each source block
	uint8_t Al = ParameterChecker::symbolAlignmentValue(); // the symbol alignment parameter

	if (ParameterChecker::areValidFECParameters(F, T, Z, N)) {
		return newLocalInstance(F, T, Z, N, Al);
	} else {
		// TODO add more exception specificity
		throw std::invalid_argument("invalid FECParameter argument");
	}
}

FECParameters FECParameters::deriveParameters(uint64_t dataLen, uint16_t payLen, uint64_t maxDBMem) {

	uint64_t F = dataLen; // the transfer length of the object, in octets
	uint16_t P = payLen; // the maximum payload size in octets, which is assumed to be a multiple of Al
	uint64_t WS = maxDBMem; // the maximum size block that is decodable in working memory, in octets (not sure about num of bits)
	uint8_t Al = ParameterChecker::symbolAlignmentValue(); // the symbol alignment parameter

	if (ParameterChecker::areValidDeriverParameters(F, P, WS)) {
		uint16_t T = P; // T = P'

		uint16_t Kt = InternalFunctions::getTotalSymbols(F, T);     // Kt = ceil(F/T)
		uint16_t topN = InternalFunctions::topInterleaverLength(T); // N_max = floor(T/(SS*Al))

		uint8_t Z = deriveZ(Kt, WS, T, Al, topN); // Z = ceil(Kt/KL(N_max))
		uint16_t N = deriveN(Kt, Z, WS, T, Al, topN); // N is the minimum n=1, ..., N_max such that ceil(Kt/Z) <= KL(n)

		return newLocalInstance(F, T, Z, N, Al);
	} else {
		// TODO add more exception specificity
		throw std::invalid_argument("invalid FECParameter argument");
	}
}

uint8_t FECParameters::deriveZ(uint16_t Kt, uint64_t WS, uint16_t T, uint8_t Al, uint16_t topN) {

	int Kl = InternalFunctions::KL(WS, T, Al, topN);
	return extra_math::ceil_div(Kt, Kl); // Z = ceil(Kt/KL(N_max))
}

int FECParameters::deriveN(uint16_t Kt, uint8_t Z, uint64_t WS, uint16_t T, uint8_t Al, uint16_t topN) {

	// N is the minimum n=1, ..., N_max such that ceil(Kt/Z) <= KL(n)
	int topK = extra_math::ceil_div(Kt, Z);
	for (int n = topN; n >= 1; n--) {
		if (topK <= InternalFunctions::KL(WS, T, Al, n)) {
			return n;
		}
	}

	throw std::runtime_error("must never be thrown");
}

FECParameters FECParameters::newLocalInstance(uint64_t F, uint16_t T, uint8_t Z, uint16_t N, uint8_t Al) {

	uint64_t commonFecOTI = ParameterIO::buildCommonFecOTI(F, T);
	uint32_t schemeSpecFecOTI = ParameterIO::buildSchemeSpecFecOTI(Z, N, Al);
	return FECParameters(commonFecOTI, schemeSpecFecOTI);
}

FECParameters::FECParameters(uint64_t common_fec_oti, uint32_t scheme_spec_fec_oti) {

	commonFecOTI = common_fec_oti;
	schemeSpecFecOTI = scheme_spec_fec_oti;
}

uint64_t FECParameters::dataLength() {

	return ParameterIO::extractDataLength(commonFecOTI);
}

uint16_t FECParameters::symbolSize() {

	return ParameterIO::extractSymbolSize(commonFecOTI);
}

uint8_t FECParameters::numberOfSourceBlocks() {

	return ParameterIO::extractNumSourceBlocks(schemeSpecFecOTI);
}

uint16_t FECParameters::interleaverLength() {

	return ParameterIO::extractInterleaverLength(schemeSpecFecOTI);
}

uint8_t FECParameters::symbolAlignment() {

	return ParameterIO::extractSymbolAlignment(schemeSpecFecOTI);
}

uint16_t FECParameters::totalSymbols() {

	return InternalFunctions::getTotalSymbols(dataLength(), symbolSize());
}
