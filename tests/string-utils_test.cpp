/*
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Hugo Arregui, FuDePAN 2011
    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE_1_0.txt in the root directory or 
    copy at http://www.boost.org/LICENSE_1_0.txt)
    
    MiLi IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
    SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
    FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.

    This is a test file.
*/

#include "google/gtest/gtest.h"
#include "google/gmock/gmock.h"
#include <map>
#include "mili/mili.h"

using namespace mili;

TEST(StringUtilsTest, lstring_test)
{
    lstring ls("helLO");
    ls[1] = 'E';

    ASSERT_TRUE(ls[2] == 'L');
    ASSERT_TRUE(ls == "HELLO");

    std::map<lstring, int> m;
    m["Hello"] = 3;
    m["Goodbye"] = 5;
    ASSERT_EQ(3, m["hELLo"]);

    ASSERT_TRUE(begins_with(ls, "HE"));
    ASSERT_TRUE(ends_with(ls, "Ello"));
}

TEST(StringUtilsTest, toupper)
{
    ASSERT_EQ("HELLO WORLD!", toupper("Hello World!"));
}

TEST(StringUtilsTest, to_string)
{
    ASSERT_EQ("123.4", to_string(123.4));
}

TEST(StringUtilsTest, to_number)
{
    int n;
    ASSERT_FALSE(to_number("abc", n));
    ASSERT_EQ(123.4f, to_number<float>("123.4"));
}

TEST(StringUtilsTest, ensure_found)
{
    std::string str = "Why?";
    ASSERT_TRUE(ensure_found(str.find_first_of("h", 0)));
    ASSERT_THROW(ensure_found(str.find_first_of(" ", 0)), StringNotFound);
    ASSERT_EQ(str.size(), ensure_found(str.find_first_of(" ", 0), str.size()));
}

TEST(StringUtilsTest, substr)
{
    ASSERT_EQ("llo Wo", substr("Hello World", Pos_(2), Count_(6)));
    ASSERT_EQ("llo W", substr("Hello World", Pos_(2), Pos_(6)));
}

