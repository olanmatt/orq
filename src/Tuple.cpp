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

#include <Tuple.h>

Tuple::Tuple(int Kprime, long X) {

	int Ki = SystematicIndices::getKIndex(Kprime);
	int S = SystematicIndices::S(Ki);
	int H = SystematicIndices::H(Ki);
	int W = SystematicIndices::W(Ki);
	int L = Kprime + S + H;
	int J = SystematicIndices::J(Ki);
	int P = L - W;
	long P1 = MatrixUtilities::ceilPrime(P);

	long A = 53591 + J * 997;
	if (A % 2 == 0) A++;

	long B = 10267 * (J + 1);

	long y = (B + X * A) % 4294967296L; // 2^^32

	long v = Rand::rand(y, 0, 1048576L); // 2^^20

	d = Deg::deg(v, W);
	a = 1 + Rand::rand(y, 1, W - 1);
	b = Rand::rand(y, 2, W);
	if (d < 4) d1 = 2 + Rand::rand(X, 3, 2L);
	else d1 = 2;
	a1 = 1 + Rand::rand(X, 4, P1 - 1);
	b1 = Rand::rand(X, 5, P1);
}

long Tuple::D() {
	return d;
}

long Tuple::A() {
	return a;
}

long Tuple::B() {
	return b;
}

long Tuple::D1() {
	return d1;
}

long Tuple::A1() {
	return a1;
}

long Tuple::B1() {
	return b1;
}
