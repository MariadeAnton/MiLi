/*
type_mapper: A minimal library that implements type mappers.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Gutson, FuDePAN 2009
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

    This is an example file.
*/

#include <vector>
#include "mili/mili.h"

using namespace mili;

declare_type_mapper(TypeMapper);
add_mapping(TypeMapper, char, int);
add_mapping(TypeMapper, unsigned int, int);
add_mapping(TypeMapper, short int, int);
add_mapping_for_pointers(TypeMapper, int);

template <class T>
class MyVector : public std::vector<map_type(TypeMapper, T)>
{};

int main()
{
    MyVector<short int> v1;
    MyVector<float> v2;

    v1.push_back(1);
    v2.push_back(1.0f);

    return 0;
}
