/*
generic_exception.h: A minimal library for generic exceptions.
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

#ifndef GENERIC_EXCEPTION
#define GENERIC_EXCEPTION

#include <exception>
#include <string>

NAMESPACE_BEGIN

template <class Hierarchy>
class GenericException : public std::exception
{
protected:
    const std::string description;

public:
    explicit GenericException(const std::string& description) :
        description(description)
    {}

    ~GenericException() throw() {};

    //! what redefinition
    virtual const char* what() const throw()
    {
        return description.c_str();
    }
};

#ifdef NO_MILI_NAMESPACE
#    define EXCEPTION_NAMESPACE
#else
#    define EXCEPTION_NAMESPACE mili
#endif

#define DEFINE_SPECIFIC_EXCEPTION_TEXT(name, subtype, text)                      \
class name : public EXCEPTION_NAMESPACE::GenericException<subtype>               \
{                                                                                \
public:                                                                          \
    name() :                                                                     \
        EXCEPTION_NAMESPACE::GenericException<subtype>(text)                     \
    {}                                                                           \
                                                                                 \
    name(const std::string& description) :                                       \
        EXCEPTION_NAMESPACE::GenericException<subtype>(text ": " + description)  \
    {}                                                                           \
}

#define DEFINE_SPECIFIC_EXCEPTION(name, subtype) DEFINE_SPECIFIC_EXCEPTION_TEXT(name, subtype, #name)

NAMESPACE_END

#endif
