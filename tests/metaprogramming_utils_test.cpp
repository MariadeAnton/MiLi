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
#include "mili/mili.h"

using namespace mili;

TEST(MetaprogrammingUtils, Select)
{
    ASSERT_TRUE(bool(template_info<Select<true, int, float>::result>::is_equal_to<int>::value));
    ASSERT_TRUE(bool(template_info<Select<false, int, float>::result>::is_equal_to<float>::value));
}

TEST(MetaprogrammingUtils, ParameterType)
{
    ASSERT_TRUE(bool(template_info<ParameterType<int>::type>::is_equal_to<int>::value));
    ASSERT_TRUE(bool(template_info<ParameterType<std::string>::type>::is_equal_to<const std::string&>::value));
    ASSERT_TRUE(bool(template_info<ParameterType<const std::string>::type>::is_equal_to<const std::string&>::value));
}

