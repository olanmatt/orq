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

#include <parameters/InternalFunctions.h>

long InternalFunctions::getPossibleTotalSymbols(long F, int T) {

	return ExtraMath::ceilDiv(F, T);
}

int InternalFunctions::getTotalSymbols(long F, int T) {

	return (int)ExtraMath::ceilDiv(F, T); // downcast never overflows since F and T are bounded
}

int InternalFunctions::topInterleaverLength(int T) {
	
	int SStimesAl = T;

	return T / SStimesAl;
}

int InternalFunctions::KL(long WS, int T, int Al, int n) {

	int K_upper_bound = (int)std::min((int)InternalConstants::K_max, (int) (WS / subSymbolSize(T, Al, n)));
	return SystematicIndices::floor(K_upper_bound);
}

long InternalFunctions::minWS(int Kprime, int T, int Al, int n) {

	return (long)SystematicIndices::ceil(Kprime) * subSymbolSize(T, Al, n);
}

int InternalFunctions::subSymbolSize(int T, int Al, int n) {

	return Al * ExtraMath::ceilDiv(T, Al * n);
}
