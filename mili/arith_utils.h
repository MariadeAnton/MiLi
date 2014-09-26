/*
arith_utils.h: A minimal library with arithmetic utilities.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Gutson & Guillermo Biset, FuDePAN 2009-2010 
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

#ifndef ARITH_UTILS_H
#define ARITH_UTILS_H

#include <cmath>
#include "compile_assert.h"

NAMESPACE_BEGIN

declare_type_mapper(ToFloatMapper);
add_mapping(ToFloatMapper, int, float);
add_mapping(ToFloatMapper, long int, float);
add_mapping(ToFloatMapper, short int, float);

template <class T>
class _bchain
{
    const T _last_value;
    bool    _last_eval;

    _bchain(T value, bool last_eval)
        : _last_value(value), _last_eval(last_eval)
    {}
public:
    _bchain(T value)
        : _last_value(value), _last_eval(true)
    {}

    _bchain(const _bchain<T>& other)
        : _last_value(other._last_value), _last_eval(other._last_eval)
    {}

    operator bool() const
    {
        return _last_eval;
    }

    bool operator!() const
    {
        return !_last_eval;
    }

#define BCHAIN_OPERATOR(op)                                                 \
    _bchain<T> operator op (T rvalue) const                                 \
    {                                                                       \
        return _bchain<T>(rvalue, _last_eval && (_last_value op rvalue));   \
    }                                                                       \
    _bchain<T> operator op (const _bchain<T>& other) const                  \
    {                                                                       \
        return _bchain<T>(other._last_value,                                \
               _last_eval && (_last_value op other._last_value));           \
    }

    BCHAIN_OPERATOR( <);
    BCHAIN_OPERATOR( <=);
    BCHAIN_OPERATOR( >);
    BCHAIN_OPERATOR( >=);
    BCHAIN_OPERATOR( ==);
    BCHAIN_OPERATOR( !=);

#undef BCHAIN_OPERATOR
};

#define BCHAIN_NONMEMBER_OPERATOR(op)                           \
template <class T>                                              \
inline _bchain<T> operator op (T value, const _bchain<T>& bch)  \
{                                                               \
    return _bchain<T>(value) op bch;                            \
}

BCHAIN_NONMEMBER_OPERATOR( <)
BCHAIN_NONMEMBER_OPERATOR( >)
BCHAIN_NONMEMBER_OPERATOR( <=)
BCHAIN_NONMEMBER_OPERATOR( >=)
BCHAIN_NONMEMBER_OPERATOR( ==)
BCHAIN_NONMEMBER_OPERATOR( !=)

#undef BCHAIN_NONMEMBER_OPERATOR

template <class T>
inline _bchain<T> bchain(T value)
{
    return _bchain<T>(value);
}

template <class T>
inline bool in_range(T val, T min, T max)
{
    return min <= bchain(val) <= max;
}

class FirstTimeFlag
{
    bool value;
public:
    FirstTimeFlag() : value(true) {}

    operator bool()
    {
        const bool ret(value);
        value = false;
        return ret;
    }

    bool operator!()
    {
        return !operator bool();
    }

    void reset()
    {
        value = true;
    }
};

template<bool N, int E, class B>
class Power;

template<int E, class B>
class Power<true, E, B>
{
public:
    //TODO[C++0x]: use decltype
    static map_type(ToFloatMapper, B) result(B b)
    {
        return Power < false, -E, B >::result(1 / static_cast<map_type(ToFloatMapper, B)>(b));
    }
};

template<int E, class B>
class Power<false, E, B>
{
public:
    //TODO[C++0x]: use decltype
    static map_type(ToFloatMapper, B) result(map_type(ToFloatMapper, B) b)
    {
        return b * Power < false, E - 1, B >::result(b);
    }
};

template<class B>
class Power<false, 0, B>
{
public:
    //TODO[C++0x]: use decltype
    static map_type(ToFloatMapper, B) result(B /*b*/)
    {
        return 1;
    }
};

//TODO[C++0x]: this template should be move inside power function
template<int E>
class IsNegative
{
public:
    enum {value = E < 0};
};

template<int E, class B>
//TODO[C++0x]: use decltype
inline map_type(ToFloatMapper, B) power(B b)
{
    return Power<IsNegative<E>::value, E, B>::result(b);
}

template <class T>
inline T square(T t)
{
    return power<2>(t);
}

template <class T>
inline T maximize(T& t, T value)
{
    if (t < value)
        t = value;

    return t;
}

template <class T>
inline T minimize(T& t, T value)
{
    if (t > value)
        t = value;

    return t;
}

declare_static_assert(floating_point_allowed);

/** Returns true iff adding x and y doesn't loose information. Assumes x > y and neither x nor y are 0. */
template <class T>
inline bool is_lossless_sum_bigsmall(T x, T y)
{
    template_compile_assert(template_info<T>::is_floating_point, floating_point_allowed);
    return (x + y != x);
}


/** Returns true iff adding x and y doesn't loose information (due to floating point representation). */
template <class T>
inline bool is_lossless_sum(T x, T y)
{
    template_compile_assert(template_info<T>::is_floating_point, floating_point_allowed);
    return x == T(0) || y == T(0) || (x + y > std::max(x, y));
}

template <class T>
//TODO[C++0x]: use decltype
inline map_type(ToFloatMapper, T) deg2rad(T deg)
{
    static const float deg2rad_ratio = M_PI / 180;
    return deg * deg2rad_ratio;
}


inline bool implies(bool p, bool q)
{
    return !p || q;
}


#if _BSD_SOURCE || _SVID_SOURCE || _XOPEN_SOURCE >= 600 || _ISOC99_SOURCE || _POSIX_C_SOURCE >= 200112L

template <class T>
//TODO[C++0x]: use decltype
inline map_type(ToFloatMapper, T) cubic_root(T a)
{
    return cbrtf(a);
}

inline double cubic_root(double a)
{
    return cbrt(a);
}

#elif XOPEN_SOURCE >= 500 || _XOPEN_SOURCE && _XOPEN_SOURCE_EXTENDED

template <class T>
inline double cubic_root(T a)
{
    return cbrt(a);
}

#else

template <class T>
//TODO[C++0x]: use decltype
inline map_type(ToFloatMapper, T) cubic_root(T a)
{
    return pow(a, 1.0f / 3.0f);
}
#endif

NAMESPACE_END

#endif
