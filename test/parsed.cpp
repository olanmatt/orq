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


#include <parsed.h>
#include <catch.h>
#include <vector>
#include <string>

TEST_CASE("Parsed::of returns a 'valid' Parsed Object", "[Parsed]")
{
    std::vector<int> test {1, 2, 3};

    Parsed< std::vector<int> > &p = Parsed< std::vector<int> >::of(test);

    SECTION("It should be valid,") {
        REQUIRE(p.is_valid());
    }

    SECTION("value() should return a copy of the object passed in.") {
        REQUIRE(p.value() == test);

        SECTION("The object that was passed in should be deep copied.") {
            std::vector<int> backup = test;
            test.push_back(4);
            REQUIRE(p.value() == backup);
        }
    }

    SECTION("failure_reason() should be empty.") {
        REQUIRE(p.failure_reason() == "");
    }
}

TEST_CASE("Parsed::invalid returns an 'invalid' Parsed Object", "[Parsed]")
{
    std::string reason = "reasons";
    Parsed<int> &p = Parsed<int>::invalid(reason);

    SECTION("It should not be valid,") {
        REQUIRE_FALSE(p.is_valid());
    }

    SECTION("value() should throw an exception") {
        REQUIRE_THROWS_AS(p.value(), std::string);

        SECTION("exception message should be the same as it's failure reason") {
            try {
                p.value();
            } catch(std::string exception) {
                REQUIRE(p.failure_reason() == exception);
            }
        }
    }

    SECTION("failure_reason() returns a copy of the string passed in.") {
        REQUIRE(p.failure_reason() == reason);

        SECTION("The object that was passed in should be deep copied.") {
            std::string backup_reason = reason;
            reason += "foo";
            REQUIRE(p.failure_reason() == backup_reason);
        }
    }
}
