/*
invariants: A minimal library for a checking invariants.
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

#ifndef INVARIANTS_H
#define INVARIANTS_H

#include <exception>

NAMESPACE_BEGIN

struct InvariantNotMet : std::exception
{
};

/* Part 1: Invariants for parameters */

namespace invariant
{
// this will be a template alias in C++0x
#define define_invariant(Name, op)              \
    template <class T, T operand>               \
    class Name                                  \
    {                                           \
            const T value;                      \
        public:                                 \
            operator T()const { return value; } \
            Name(T value) : value(value)        \
            {                                   \
                if (!(value op operand))        \
                    throw InvariantNotMet();    \
            }                                   \
    }

define_invariant(lt, <);
define_invariant(le, <=);
define_invariant(eq, ==);
define_invariant(ne, !=);
define_invariant(ge, >=);
define_invariant(gt, >);

template <class T>
class NeverNull
{
    T* const ptr;
public:
    NeverNull(T* ptr) : ptr(ptr)
    {
        if (ptr == NULL)
            throw InvariantNotMet();
    }
    operator T* () const
    {
        return ptr;
    }
};

template <class T, T Min, T Max>
struct InRange : ge<T, Min>, le<T, Max>
{
    InRange(T t) : ge<T, Min>(t), le<T, Max>(t) {}
};
}

/* Part 2: Class Invariants */
/* This is implemented using the prepos_caller technique. */

template <class T, bool (*Invariant)(const T&)>
class InvariantClass
{
    T& t;
public:
    struct Temp
    {
        T& t;
        Temp(T& t) : t(t) {}
        T* operator -> () const
        {
            return &t;
        }

        ~Temp()
        {
            if (!Invariant(t))
                throw InvariantNotMet();
        }
    };

    InvariantClass(T& t) : t(t) {};

    Temp operator -> () const
    {
        return Temp(t);
    }
};

NAMESPACE_END

#endif
