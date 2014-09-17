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

TEST(PromotionDisable, StrictRules)
{
    ASSERT_TRUE(bool(StrictRules<float, float>::value));
    ASSERT_FALSE(bool(StrictRules<int, float>::value));
}

TEST(PromotionDisable, FloatingPoints)
{
    ASSERT_TRUE(bool(FloatingPoints<float, float>::value));
    ASSERT_TRUE(bool(FloatingPoints<float, double>::value));
    ASSERT_FALSE(bool(FloatingPoints<int, float>::value));
}

TEST(PromotionDisable, RulesCondition)
{
    ASSERT_TRUE(bool(RulesCondition<true>::value));
    ASSERT_FALSE(bool(RulesCondition<false>::value));
}

TEST(PromotionDisable, NotNarrowing)
{
    ASSERT_FALSE(bool(NotNarrowing<int, char>::value));
    ASSERT_TRUE(bool(NotNarrowing<char, int>::value));
    ASSERT_FALSE(bool(NotNarrowing<float, int>::value));
    ASSERT_TRUE(bool(NotNarrowing<float, float>::value));
}

float f(Restrict<float> rf)
{
    return rf + 1.0f;
}

TEST(PromotionDisable, test)
{
    f(1.0f);
    //f(1); cannot test this
}
