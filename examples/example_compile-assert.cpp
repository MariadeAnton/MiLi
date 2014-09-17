/*
compile_assert: A minimal library supporting compile time (static) assertions,
    a la C++0x.
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

#include "mili/mili.h"

using namespace mili;

generic_assert(sizeof(int) == 4);

declare_static_assert(this_assertion_will_always_fail);
declare_static_assert(pointers_not_allowed_assert);

template <class T> struct MyType
{
    template_compile_assert(!template_is_pointer<T>::value, pointers_not_allowed_assert);
};

int main()
{
    compile_assert(sizeof(char) == 2, this_assertion_will_always_fail); // fails

    MyType<char*> mt1;  // fails
    MyType<char>  mt2;  // OK
    return 0;
}
