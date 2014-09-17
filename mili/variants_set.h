/*
VariantsSet: A minimal library that implements a set of variables of heterogenic types.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Ezequiel S. Velez
                  Daniel Gutson, FuDePAN 2010
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

#ifndef VARIANTS_SET_H
#define VARIANTS_SET_H

#include <string>
#include <map>

NAMESPACE_BEGIN

struct VariantsSetException : std::exception {};
struct BadElementType : VariantsSetException {};
struct BadElementName : VariantsSetException {};

typedef std::string ElementName;

class VariantsSet
{
    typedef std::map<ElementName, std::string> VariantsSets;

    VariantsSets elements;

public:
    /* typedef to simulate STL */
    typedef VariantsSets::iterator iterator;
    typedef VariantsSets::const_iterator const_iterator;
    typedef VariantsSets::value_type value_type;
    typedef VariantsSets::reference reference;
    typedef VariantsSets::const_reference const_reference;

    /* Returns a const_iterator pointing to the beginning of the VariantsSet. */
    inline const_iterator begin() const
    {
        return elements.begin();
    }
    /* Returns a const_iterator pointing to the end of the VariantsSet. */
    inline const_iterator end() const
    {
        return elements.end();
    }
    /* Returns a iterator pointing to the beginning of the VariantsSet. */
    inline iterator begin()
    {
        return elements.begin();
    }
    /* Returns a iterator pointing to the end of the VariantsSet. */
    inline iterator end()
    {
        return elements.end();
    }

    /* returns the element called name */
    template <class T>
    T get_element(const ElementName& name) const throw(BadElementType, BadElementName)
    {
        const std::map<ElementName, std::string>::const_iterator it = elements.find(name);
        T element;
        if (it != elements.end())
        {
            if (!from_string<T>(it->second, element))
                throw BadElementType();
        }
        else
            throw BadElementName();
        return element;
    }

    template <class T>
    void get_element(const ElementName& name, T& element) const throw(BadElementType, BadElementName)
    {
        const std::map<ElementName, std::string>::const_iterator it = elements.find(name);
        if (it != elements.end())
        {
            if (!from_string<T>(it->second, element))
                throw BadElementType();
        }
        else
            throw BadElementName();
    }


    /* get_element, nothrow versions */
    template <class T>
    bool get_element(const ElementName& name, T& element, const std::nothrow_t&) const throw()
    {
        const std::map<ElementName, std::string>::const_iterator it = elements.find(name);
        const bool success_name(it != elements.end());
        bool success_type(false);
        if (success_name)
            success_type = from_string<T>(it->second, element);
        return (success_name && success_type);
    }

    /* inserts the element in the varianteSet. */
    template <class T>
    void insert(const ElementName& name, const T& element)
    {
        elements[name] = to_string(element);
    }

    bool empty() const
    {
        return elements.empty();
    }

    void erase(const ElementName& name) throw(BadElementName)
    {
        const std::map<ElementName, std::string>::const_iterator it = elements.find(name);
        if (it != elements.end())
            elements.erase(name);
        else
            throw BadElementName();
    }

    void clear()
    {
        elements.clear();
    }

    size_t size() const
    {
        return elements.size();
    }

    VariantsSet()
        : elements()
    {}
};

NAMESPACE_END

#endif
