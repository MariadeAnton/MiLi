/*
prepos_caller: A minimal library for wrapping object methods calls.
    This is the main class. Use it passing the pre-call and pos-call.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Gutson, FuDePAN 2008-2009
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

#ifndef PREPOS_H
#define PREPOS_H

NAMESPACE_BEGIN

template <class T, class Pre, class Pos>
struct PrePosCaller
{
    struct Temp
    {
        T& t;
        Pos& pos;

        Temp(T& t, Pos& pos) : t(t), pos(pos) {}

        T& operator -> () const
        {
            return t;
        }

        ~Temp()
        {
            pos();
        }
    };

    T& t;
    Pre& pre;
    Pos& pos;

    PrePosCaller(T& t, Pre& pre, Pos& pos) : t(t), pre(pre), pos(pos) {}

    Temp operator -> () const
    {
        pre();
        return Temp(t, pos);
    }
};

template <class T, class Pre, class Pos>
struct PrePosCaller<T*, Pre, Pos>
{
    struct Temp
    {
        T* t;
        Pos& pos;

        Temp(T* t, Pos& pos) : t(t), pos(pos) {}

        T* operator -> () const
        {
            return t;
        }

        ~Temp()
        {
            pos();
        }
    };

    T* t;
    Pre& pre;
    Pos& pos;

    PrePosCaller(T* t, Pre& pre, Pos& pos) : t(t), pre(pre), pos(pos) {}

    Temp operator -> () const
    {
        pre();
        return Temp(t, pos);
    }
};

template <class T, class Pre, class Pos>
struct PrePosCaller<T* const, Pre, Pos>
{
    struct Temp
    {
        T* const t;
        Pos& pos;
        Temp(T* t, Pos& pos) : t(t), pos(pos) {}

        T* operator -> () const
        {
            return t;
        }

        ~Temp()
        {
            pos();
        }
    };

    T* const t;
    Pre& pre;
    Pos& pos;

    PrePosCaller(T* t, Pre& pre, Pos& pos) : t(t), pre(pre), pos(pos) {}

    Temp operator -> () const
    {
        pre();
        return Temp(t, pos);
    }
};

NAMESPACE_END

#endif
