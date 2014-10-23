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

#ifndef INCLUDE_PARSED_H_
#define INCLUDE_PARSED_H_

#include <string>
#include <stdexcept>

template <typename V>
class Parsed
{
public:
    static Parsed<V> &of(V value);
    static Parsed<V> &invalid(std::string failureReason);

    virtual bool is_valid() = 0;
    virtual V value() = 0;
    virtual std::string failure_reason() = 0;

protected:
    Parsed() { }

private:
    class ParsedValue;

    class InvalidValue;
};

/* I get link error when using any of these functions unless they're fully
 * defined in the file that is to be included. So I'm doing just that until I
 * can find a better solution */

template <typename V>
Parsed<V> &Parsed<V>::of(V value)
{
    return *(new ParsedValue(value));
}

template <typename V>
Parsed<V> &Parsed<V>::invalid(std::string reason)
{
    return *(new InvalidValue(reason));
}

template <typename V>
class Parsed<V>::ParsedValue : public Parsed<V>
{
public:
    ParsedValue(const V &value) : Parsed()
    {
        value_ = value;
    }
    ~ParsedValue(void)
    {
        delete value_;
    }

    bool is_valid()
    {
        return true;
    }
    V value()
    {
        return this->value_;
    }
    std::string failure_reason()
    {
        return "";
    }

private:
    V value_;
};

template <typename V>
class Parsed<V>::InvalidValue : public Parsed<V>
{
public:
    InvalidValue(const std::string &reason) : Parsed()
    {
        reason_ = reason;
    }
    ~InvalidValue(void)
    {
        delete reason_;
    }

    bool is_valid(void)
    {
        return false;
    }
    V value(void)
    {
        throw failure_reason();
    }
    std::string failure_reason(void)
    {
        return this->reason_;
    }

private:
    std::string reason_;
};

#endif  // INCLUDE_PARSED_H_
