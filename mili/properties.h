/*
properties: A minimal library that implements object properties.
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

#ifndef PROPERTIES_H
#define PROPERTIES_H

NAMESPACE_BEGIN

template <class T, class Type, Type(T::*Getter)() const>
struct PropertyR
{
    operator Type() const
    {
        return (This()->*Getter)();
    }

private:
    const T* This() const
    {
        return reinterpret_cast<const T*>(this);
    }
};

template <class T, class Type, void (T::*Setter)(Type)>
struct PropertyW
{
    PropertyW<T, Type, Setter> operator = (Type t)
    {
        (This()->*Setter)(t);
        return *this;
    }

private:
    T* This()
    {
        return reinterpret_cast<T*>(this);
    }
};

template <class T, class Type, Type(T::*Getter)() const, void (T::*Setter)(Type)>
struct PropertyRW : PropertyR<T, Type, Getter>, PropertyW<T, Type, Setter>
{
    using PropertyW<T, Type, Setter>:: operator =;
};


#define BEGIN_PROPERTIES union {
#define END_PROPERTIES };

// alternate way:
#define PROPERTIES  union

#if 0
/* Not available */
template <class T, class Type, Type(T::*Member), Type(*Function)(Type)>
struct PropertyFR
{
    operator Type() const
    {
        return *Function(This()->*Member)();
    }

private:
    const T* This() const
    {
        return reinterpret_cast<const T*>(this);
    }
};

template <class T, class Type, Type(T::*Member), Type(*Function)(Type)>
struct PropertyFW
{
    void operator = (Type t)
    {
        (This()->*Member) = *Function(t);
    }

private:
    T* This()
    {
        return reinterpret_cast<T*>(this);
    }
};

template <class T, class Type, Type(T::*Member), Type(*FunctionR)(Type), Type(*FunctionW)(Type)>
struct PropertyFRW : PropertyFR<T, Type, Member, FunctionR>, PropertyFW<T, Type, Member, FunctionW>
{
    using PropertyFW<T, Type, Member, FunctionW>:: operator =;
};
#endif

NAMESPACE_END

#endif
