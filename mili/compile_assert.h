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
*/

#ifndef COMPILE_ASSERT_H
#define COMPILE_ASSERT_H

//NAMESPACE_BEGIN

#ifndef __GXX_EXPERIMENTAL_CXX0X__  // replace this by __cplusplus > 199711L when available


#ifdef COMPILE_ASSERT_TEST
#define fail_value() typedef float CompileTimeAssertion;
#else
#define fail_value()
#endif

#define declare_static_assert(name)     \
template <bool Condition>               \
struct name                             \
{                                       \
    typedef int CompileTimeAssertion;   \
};                                      \
template <>                             \
struct name<false>                      \
{                                       \
    fail_value()                        \
}

#define compile_assert(condition, name) \
    typedef name<condition >::CompileTimeAssertion name##__

#define template_compile_assert(condition, name) \
    typedef typename name<condition >::CompileTimeAssertion name##__

declare_static_assert(GenericAssertion);

#define generic_assert(condition)   \
    compile_assert(condition, GenericAssertion)

#define template_generic_assert(condition)   \
    compile_assert(condition, GenericAssertion)

#else
#   define declare_static_assert(name)
#   define compile_assert(condition, name) static_assert(condition, #name)
#   define template_compile_assert(condition, name) static_assert(condition, #name)
#   define generic_assert(condition) static_assert(condition, #condition)
#   define template_generic_assert(condition) static_assert(condition, #condition)
#endif

//NAMESPACE_END

#endif

