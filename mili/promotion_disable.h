/*
promotion_disable.h: A minimalistic library to disable undesired
    type promotions in C++.
    This file is part of the MiLi Minimalistic Library.


    Copyright (C) Daniel Gutson, FuDePAN 2009
                  Hugo Arregui, FuDePAN 2012
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

#ifndef PROMOTION_DISABLE_H
#define PROMOTION_DISABLE_H

#include "compile_assert.h"
#include "template_info.h"

NAMESPACE_BEGIN

/* RulesCondition<cond> will only allow conversion when cond==true */
template <bool C>
struct RulesCondition
{
    enum { value = C };
};

/* StrictRules disables any conversion; only T --> T allowed */
template <class T, class U> struct StrictRules : RulesCondition<type_equal<T, U>::value>
{};

/* FloatingPoints allows T-->T, plus Double to Float */
template <class T, class U>
struct FloatingPoints : StrictRules<T, U>
{};

template <>
struct FloatingPoints<float, double>
{
    enum { value = true };
};

//[> disable conversion depending on size <]
template <class T, class U>
struct NotNarrowing : RulesCondition < sizeof(T) <= sizeof(U) >
{};

//[> disable conversion from int to float, if they have the same size <]
template <>
struct NotNarrowing<float, int>
{
    enum { value = false };
};

declare_static_assert(invalid_conversion);

template < class T, template <class X, class Y> class ConversionRules = StrictRules >
class Restrict
{
    const T value;
public:
    template <class U>
    Restrict(U u) :
        value(u)
    {
        typedef ConversionRules<T, U> ConversionType;
        template_compile_assert(ConversionType::value, invalid_conversion);
    }

    operator T() const
    {
        return value;
    }
};

NAMESPACE_END

#endif
