/*
factory_registry: A simple way to registry derived classes without .h file
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Leandro Ramos, FuDePAN 2012
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

//WARNING FactoryRegistry should NOT be used within static libraries
#ifndef FACTORY_REGISTRY_H
#   error Internal header file, DO NOT include this.
#endif
#include<string>

template <class BaseClass, class Key = std::string>
class FactoryRegistry
{
private:
    Factory<Key, BaseClass> fc;
    static FactoryRegistry<BaseClass, Key>* instance;
    unsigned int users;

    FactoryRegistry(): users(0) {}

    template <class DerivedClass>
    void _register_factory(const Key& k)
    {
        ++users;
        fc.register_factory<DerivedClass>(k);
    }
    BaseClass* _new_class(const Key& k)
    {
        return fc.new_class(k);
    }
    bool _deregister_factory()
    {
        --users;
        return (users == 0);
    }
public:
    template<class DerivedClass>
    static void register_factory(const Key& k)
    {
        if (instance == NULL)
            instance = new FactoryRegistry<BaseClass, Key>;
        instance->_register_factory<DerivedClass>(k);
    }
    static BaseClass* new_class(const Key& k)
    {
        return instance->_new_class(k);
    }
    static void deregister_factory()
    {
        if (instance->_deregister_factory())
        {
            delete instance;
            instance = NULL;
        }
    }

};
template<class Base, class Key> FactoryRegistry<Base, Key>* FactoryRegistry<Base, Key>::instance = NULL;

template<class BaseClass, class DerivedClass, class Key>
class Registerer
{
public:
    Registerer(const Key& k)
    {
        mili::FactoryRegistry<BaseClass, Key>::template register_factory<DerivedClass>(k);
    }
    ~Registerer()
    {
        mili::FactoryRegistry<BaseClass, Key>::deregister_factory();
    }
};

#define REGISTER_FACTORIZABLE_CLASS(BaseClassName, DerivedClassName, keytype, key)           \
    static mili::Registerer<BaseClassName,DerivedClassName,keytype>  r##DerivedClassName(key)
