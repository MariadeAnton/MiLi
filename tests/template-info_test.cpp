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
#include <vector>
#include <set>
#include "mili/mili.h"

using namespace mili;

struct S {};

TEST(TemplateInfoTest, is_native)
{
    ASSERT_FALSE(bool(template_info<S>::is_native));
    ASSERT_TRUE(bool(template_info<char>::is_native));
    ASSERT_TRUE(bool(template_info<const char>::is_native));
}

TEST(TemplateInfoTest, is_integral)
{
    ASSERT_TRUE(bool(template_info<int>::is_integral));
}

TEST(TemplateInfoTest, is_floating_point)
{
    ASSERT_FALSE(bool(template_info<int>::is_floating_point));
    ASSERT_TRUE(bool(template_info<float>::is_floating_point));
    ASSERT_TRUE(bool(template_info<double>::is_floating_point));
}

TEST(TemplateInfoTest, is_pointer)
{
    ASSERT_TRUE(bool(template_info<int*>::is_pointer));
    ASSERT_TRUE(bool(template_info<int* const>::is_pointer));
}

TEST(TemplateInfoTest, is_reference)
{
    ASSERT_TRUE(bool(template_info<int&>::is_reference));
    ASSERT_TRUE(bool(template_info<const int& >::is_reference));
}

TEST(TemplateInfoTest, is_same_size)
{
    ASSERT_EQ(int(sizeof(int) == sizeof(long int)), bool(template_info<int>::is_same_size<long int>::value));
}

TEST(TemplateInfoTest, is_container)
{
    ASSERT_TRUE(bool(template_info<std::vector<int> >::is_container));
    ASSERT_TRUE(bool(template_info<const std::vector<int> >::is_container));
    ASSERT_TRUE(bool(template_info<std::set<int> >::is_container));
    ASSERT_TRUE(bool(template_info<std::list<int> >::is_container));
    ASSERT_TRUE(bool(template_info<std::multiset<int> >::is_container));
    ASSERT_TRUE(bool(template_info<std::map<int, int> >::is_container));
    ASSERT_TRUE(bool(template_info<const std::map<int, int> >::is_container));
    ASSERT_TRUE(bool(template_info<std::multimap<int, int> >::is_container));
}

TEST(TemplateInfoTest, is_const)
{
    ASSERT_TRUE(bool(template_info<const int>::is_const));
    ASSERT_TRUE(bool(template_info<int* const>::is_const));
    ASSERT_FALSE(bool(template_info<const int*>::is_const));
}

TEST(TemplateInfoTest, is_basic_script)
{
    ASSERT_TRUE(bool(template_info<std::string>::is_basic_string));
    ASSERT_TRUE(bool(template_info<const std::string>::is_basic_string));
}

TEST(MetaprogrammingUtils, Unconst)
{
    ASSERT_TRUE(bool(template_info<Unconst<std::string>::type>::is_equal_to<std::string>::value));
    ASSERT_TRUE(bool(template_info<Unconst<std::string*>::type>::is_equal_to<std::string*>::value));
    ASSERT_TRUE(bool(template_info<Unconst<std::string&>::type>::is_equal_to<std::string&>::value));
    ASSERT_TRUE(bool(template_info<Unconst<const std::string>::type>::is_equal_to<std::string>::value));
    ASSERT_TRUE(bool(template_info<Unconst<std::string* const>::type>::is_equal_to<std::string*>::value));
    ASSERT_TRUE(bool(template_info<Unconst<std::string&>::type>::is_equal_to<std::string&>::value));
}
