/*
coroutines: A minimal library that implements coroutines.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Gutson, FuDePAN 2010
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

#ifndef COROUTINES_H
#define COROUTINES_H

NAMESPACE_BEGIN

class Coroutine
{
protected:
    int yield_point;
public:
    Coroutine() :
        yield_point(0)
    {}
};

#define BEGIN_COROUTINE     \
    switch(yield_point)     \
    {                       \
        case 0:

#define mili_yield(value)       \
    do                          \
    {                           \
        yield_point = __LINE__; \
        return (value);         \
        case __LINE__:;         \
    }                           \
    while(0)

// exit_coroutine breaks the structure and is discouraged.
#define exit_coroutine(ret) \
    do                      \
    {                       \
        yield_point = 0;    \
        return (ret);       \
    }                       \
    while(0)

#define END_COROUTINE(ret)  \
    }                       \
    exit_coroutine(ret)

NAMESPACE_END

#endif

