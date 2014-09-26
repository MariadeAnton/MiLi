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

#include <string>
#include "google/gtest/gtest.h"
#include "google/gmock/gmock.h"
#include "mili/mili.h"

using namespace mili;

TEST(VariantsSetTest, test)
{
    VariantsSet variantSet;
    ElementName str = "greeting";
    variantSet.insert("number", 3);
    variantSet.insert(str, "hello");
    variantSet.insert("temperature", 0.1f);

    ASSERT_EQ(3, variantSet.size());

    int ie = 0;
    variantSet.get_element("number", ie);
    ASSERT_EQ(3, ie);

    std::string is;
    variantSet.get_element(str, is);
    ASSERT_EQ("hello", is);

    ASSERT_EQ("hello", variantSet.get_element<std::string>(str));

    float f;
    ASSERT_THROW(variantSet.get_element("float", f), BadElementName);

    variantSet.erase("temperature");
    ASSERT_EQ(2, variantSet.size());
}
