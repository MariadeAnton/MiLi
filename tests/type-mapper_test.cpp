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
#include "mili/mili.h"

using namespace mili;

declare_type_mapper(TypeMapper);
add_mapping(TypeMapper, char, int);
add_mapping(TypeMapper, unsigned int, int);
add_mapping(TypeMapper, short int, int);
add_mapping_for_pointers(TypeMapper, int);

template<class T, class R>
struct Equal
{
    enum { value = false };
};

template<class T>
struct Equal<T, T>
{
    enum { value = true };
};

TEST(TypeMapperTest, test)
{
    bool v = Equal<int, map_type_(TypeMapper, char)>::value;
    ASSERT_TRUE(v);
    v = Equal<int, map_type_(TypeMapper, void*)>::value;
    ASSERT_TRUE(v);
    v = Equal<unsigned char, map_type_(TypeMapper, unsigned char)>::value;
    ASSERT_TRUE(v);
}
