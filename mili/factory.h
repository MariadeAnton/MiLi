/*
factory: A minimal library for a generic factory.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Gutson and Marcelo Caro, FuDePAN 2009
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

#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include "delete_container.h"

NAMESPACE_BEGIN

template < class Key, class Base, class ConstructorParameterType = void >
class Factory
{
    struct Creator
    {
        virtual Base* create(ConstructorParameterType p) const = 0;
        virtual ~Creator() {}
    };

    std::map<Key, Creator*> _creators;

public:
    template <class DerivedClass>
    void register_factory(const Key& key)
    {
        class ConcreteCreator : public Creator
        {
            virtual Base* create(ConstructorParameterType p) const
            {
                return new DerivedClass(p);
            }
        };

        _creators[key] = new ConcreteCreator;
    }

    Base* new_class(const Key& key, ConstructorParameterType p) const
    {
        typename std::map<Key, Creator*>::const_iterator it = _creators.find(key);

        if (it != _creators.end())
            return it->second->create(p);
        else
            return NULL;
    }

    ~Factory()
    {
        delete_container(_creators);
    }
};

template <class Key, class Base>
class Factory<Key, Base, void>
{
    struct Creator
    {
        virtual Base* create() const = 0;
        virtual ~Creator() {}
    };

    std::map<Key, Creator*> _creators;

public:
    template <class DerivedClass>
    void register_factory(const Key& key)
    {
        class ConcreteCreator : public Creator
        {
            virtual Base* create() const
            {
                return new DerivedClass;
            }
        };

        _creators[key] = new ConcreteCreator;
    }

    Base* new_class(const Key& key) const
    {
        typename std::map<Key, Creator*>::const_iterator it = _creators.find(key);

        if (it != _creators.end())
            return it->second->create();
        else
            return NULL;
    }

    ~Factory()
    {
        delete_container(_creators);
    }
};

#define FACTORY_REGISTRY_H
#include "factory_registry.h"
#undef FACTORY_REGISTRY_H

NAMESPACE_END

#endif
