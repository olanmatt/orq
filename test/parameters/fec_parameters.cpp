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

#include <catch.h>
#include <parameters/fec_parameters.h>
#include <parameters/internal_constants.h>

TEST_CASE("fec_parameters can be created, encoded into OTIs, then restored",
          "[fec_parameters]")
{
    fec_parameters f = fec_parameters::new_parameters(1024, 16, 64);

    REQUIRE(f.data_length() == 1024LLU);
    REQUIRE(f.symbol_size() == 16);
    REQUIRE(f.num_source_blocks() == 64);
    REQUIRE(f.interleaver_length() == 1);
    REQUIRE(f.symbol_alignment() == 1);
    REQUIRE(f.total_symbols() == 64);
}

TEST_CASE("Test cases for values that do not satisfy proper parameter values "
          "for new_parameters",
          "[fec_parameters]")
{
    REQUIRE_THROWS(fec_parameters::new_parameters(0, 0, 0));
}


TEST_CASE("Test case for the lower limits of 'derive_parameters' function for "
          "valid numerical inputs that pass through if statement" ,
          "[fec_parameters]")
{
    fec_parameters f = fec_parameters::derive_parameters(1, internal_constants::Al,
                       10);

    REQUIRE(f.data_length() == 1);
    REQUIRE(f.symbol_size() == 1);
    REQUIRE(f.num_source_blocks() == 1);
    REQUIRE(f.interleaver_length() == 1);
}


TEST_CASE("Test case for the upper limits of 'derive_parameters' function for "
          "valid numerical inputs that pass througuh if statement" ,
          "[fec_parameters]")
{
    fec_parameters f = fec_parameters::derive_parameters(946270874880LLU, 65535,
                       3696370605LU);
    REQUIRE(f.data_length() == 946270874880LLU);
    REQUIRE(f.symbol_size() == 65535);
    REQUIRE(f.num_source_blocks() == 256);
    REQUIRE(f.interleaver_length() == 1);
}

TEST_CASE("Test case for the upper limits of 'derive_parameters' function for "
          "valid numeasdfrical inputs that pass througuh if statement" ,
          "[fec_parameters]")
{
    fec_parameters f = fec_parameters::derive_parameters(1024000LU, 5120, 512000);
    REQUIRE(f.num_source_blocks() == 3);
}

TEST_CASE("Test case for values that do not satisfy proper parameter values "
          "for derive_parameters",
          "[fec_parameters]")
{
    REQUIRE_THROWS(fec_parameters::new_parameters(0, internal_constants::Al - 1,
                   0));
}
