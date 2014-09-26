/*
string_utils: A minimal library with string utilities.
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

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <ctype.h>
#include <string>
#include <cstring>
#include <sstream>

NAMESPACE_BEGIN

template <class NORMALIZER>
struct normalized_string : std::string
{
    class normalized_char
    {
        NORMALIZER normalize;
        std::string::value_type& c;
    public:
        normalized_char(std::string::value_type& c)
            : c(c)
        {}

        normalized_char(const normalized_char& other)
            : c(other.c)
        {}

        operator std::string::value_type() const
        {
            return c;
        }

        normalized_char& operator = (std::string::value_type other)
        {
            c = normalize(other);
            return *this;
        }

        bool operator == (std::string::value_type other) const
        {
            return c == normalize(other);
        }

        bool operator != (std::string::value_type other) const
        {
            return c != normalize(other);
        }

        // TODO: implement ++, --, +=, -=, etc.
    };

    void normalize()
    {
        NORMALIZER normalize;
        const size_t max = size();
        for (size_t i = 0; i < max; i++)
            std::string::operator[](i) = normalize(std::string::operator[](i));
    }

    normalized_string()
        : std::string()
    {}

    normalized_string(const normalized_string<NORMALIZER>& other)
        : std::string(other)
    {}

    normalized_string(const std::string& str)
        : std::string(str)
    {
        normalize();
    }

    normalized_string(const char* cstr)
        : std::string(cstr)
    {
        normalize();
    }

#define SELF_NORMALIZED_OP(op)                                                              \
    normalized_string<NORMALIZER>& operator op (const normalized_string<NORMALIZER>& other) \
    {                                                                                       \
        std::string::operator op (other);                                                   \
        return *this;                                                                       \
    }                                                                                       \
                                                                                            \
    normalized_string<NORMALIZER>& operator op (const std::string& other)                   \
    {                                                                                       \
        std::string::operator op (other);                                                   \
        normalize();                                                                        \
        return *this;                                                                       \
    }                                                                                       \
                                                                                            \
    normalized_string<NORMALIZER>& operator op (const char* cstr)                           \
    {                                                                                       \
        std::string::operator op (cstr);                                                    \
        normalize();                                                                        \
        return *this;                                                                       \
    }                                                                                       \
                                                                                            \
    normalized_string<NORMALIZER>& operator op (char c)                                     \
    {                                                                                       \
        std::string::operator op (NORMALIZER(c));                                           \
        return *this;                                                                       \
    }

    SELF_NORMALIZED_OP( =);
    SELF_NORMALIZED_OP( +=);

    normalized_string<NORMALIZER> operator + (const normalized_string<NORMALIZER>& other) const
    {
        normalized_string<NORMALIZER> tmp(*this);
        return (tmp += other);
    }

    normalized_string<NORMALIZER> operator + (const std::string& other) const
    {
        normalized_string<NORMALIZER> tmp(*this);
        return (tmp += other);
    }

    normalized_string<NORMALIZER> operator + (char c) const
    {
        normalized_string<NORMALIZER> tmp(*this);
        return (tmp += c);
    }

#define BOOL_NORMALIZED_OP(op)                                          \
    bool operator op (const normalized_string<NORMALIZER>& other) const \
    {                                                                   \
        return static_cast<const std::string&>(*this) op (other);       \
    }                                                                   \
                                                                        \
    bool operator op (const char* s) const                              \
    {                                                                   \
        return (*this) op normalized_string<NORMALIZER>(s);             \
    }                                                                   \
                                                                        \
    bool operator op (const std::string& s) const                       \
    {                                                                   \
        return *this op normalized_string<NORMALIZER>(s);               \
    }

    BOOL_NORMALIZED_OP( ==);
    BOOL_NORMALIZED_OP( !=);
    BOOL_NORMALIZED_OP( <);
    BOOL_NORMALIZED_OP( <=);
    BOOL_NORMALIZED_OP( >=);
    BOOL_NORMALIZED_OP( >);

    //using std::string::operator [];

    normalized_char operator[](size_t index)
    {
        return normalized_char(std::string::operator[](index));
    }

    normalized_char operator[](size_t index) const
    {
        return normalized_char(std::string::operator[](index));
    }

    std::string::size_type find(const normalized_string<NORMALIZER>& other) const
    {
        return std::string::find(other);
    }

    std::string::size_type find(const std::string& str) const
    {
        return find(normalized_string<NORMALIZER>(str));
    }

    std::string::size_type find(const char* cstr) const
    {
        return find(normalized_string<NORMALIZER>(cstr));
    }

    std::string::size_type find(std::string::value_type v) const
    {
        return std::string::find(NORMALIZER(v));
    }

};

struct TO_UPPER_FUNCTOR
{
    int operator()(int c) const
    {
        return toupper(c);
    }
};

struct TO_LOWER_FUNCTOR
{
    int operator()(int c) const
    {
        return tolower(c);
    }
};

typedef normalized_string<TO_UPPER_FUNCTOR> ustring;
typedef normalized_string<TO_LOWER_FUNCTOR> lstring;

inline std::string tolower(const std::string& s)
{
    return lstring(s);
}

inline std::string toupper(const std::string& s)
{
    return ustring(s);
}

template <class T> inline size_t size(const T& t)
{
    return t.size();
}

inline size_t size(const char* cstr)
{
    return std::strlen(cstr);
}

template <class S, class B>
inline bool begins_with(const S& s, const B& beginning)
{
    // TODO: improve
    return s.find(beginning) == 0;
}

template <class S, class E>
inline bool ends_with(const S& s, const E& ending)
{
    // TODO: improve
    const typename S::size_type position = s.find(ending);
    if (position == S::npos)
        return false;
    else
        return (s.size() - position) == size(ending);
}

template <class Number>
inline std::string to_string(Number n)
{
    std::stringstream ss;
    ss << n;
    return ss.str();
}

template <class T>
inline T from_string(const std::string& s)
{
    T t;
    std::stringstream ss(s);
    ss >> t;
    return t;
}

template <class T>
inline bool from_string(const std::string& s, T& t)
{
    std::stringstream ss(s);
    return (ss >> t);
}

/* Special case: string -> string */

template <>
inline std::string from_string<std::string>(const std::string& s)
{
    return s;
}

template <>
inline bool from_string<std::string>(const std::string& s, std::string& t)
{
    t = s;
    return true;
}

/* to_number is obsolete. from_string should be used instead. */
template <class Number>
inline Number to_number(const std::string& s)
{
    return from_string<Number>(s);
}

template <class Number>
inline bool to_number(const std::string& s, Number& n)
{
    return from_string(s, n);
}

// Remove whitespace at both sides
inline std::string trim(const std::string& s)
{
    std::string text(s);

    std::string::size_type positionStart = text.find_first_not_of(' ');
    text.erase(0, positionStart);
    std::string::size_type positionEnd = text.find_last_not_of(' ');
    text.erase(positionEnd + 1);

    return text;
}

struct StringNotFound : std::exception {};

inline std::string::size_type ensure_found(std::string::size_type found) throw(StringNotFound)
{
    if (found != std::string::npos)
        return found;
    else
        throw StringNotFound();
}

inline std::string::size_type ensure_found(std::string::size_type found, std::string::size_type default_value)
{
    if (found != std::string::npos)
        return found;
    else
        return default_value;
}

struct Count_
{
    explicit Count_(size_t count) :
        _count(count)
    {
    }

    const size_t _count;
};

struct Pos_
{
    explicit Pos_(size_t pos) :
        _pos(pos)
    {
    }

    const size_t _pos;
};

inline std::string substr(const std::string& str, const Pos_& start, const Count_& count)
{
    return str.substr(start._pos, count._count);
}

inline std::string substr(const std::string& str, const Pos_& start, const Pos_& end)
{
    return str.substr(start._pos, end._pos - start._pos + 1);
}

NAMESPACE_END

#endif
