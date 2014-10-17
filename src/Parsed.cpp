/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Matt Olan, Prajjwal Bhandari
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


#include <string>
#include <Parsed.h>


template <class T>
class ParsedValue : private Parsed<T> {

    private:
        T val;
        ParsedValue(T &value) {
            val = value;
        };

    public:
        bool isValid() {
            return true;
        };

        T value() {
            return val;
        };

        std::string failureReason() {
            return "";
        };
};

template <class T>
class InvalidValue : private Parsed<T> {

    private:
        std::string failReason;

        InvalidValue(std::string failureReason) {
            failReason = failureReason;
        };

    public:
        bool isValid(void) {
            return false;
        };

        T value(void) {
            return NULL;
        }; // XXX throw expecpion

        std::string failureReason(void) {
            return failReason;
        };
};


template <class V>
Parsed<V> Parsed<V>::of(const V &value) {
    return ParsedValue<V>(value);
};

template <class V>
Parsed<V> Parsed<V>::invalid(const std::string &failureReason) {
    return InvalidValue<V>(value);
};
