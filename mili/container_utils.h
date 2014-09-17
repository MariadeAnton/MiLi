/*
container_utils: A minimal library with generic STL container utilities.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Gutson & Ezequiel S. Velez, FuDePAN 2009-2010
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

#ifndef CONTAINER_UTILS_H
#define CONTAINER_UTILS_H

// Supported containers for mili::find() and mili::contains():
#include <map>
#include <vector>
#include <list>
#include <set>
#include <new>
#include <queue>

#include <algorithm>
#include <exception>
#include "ranker.h"
//#include <iterator>

NAMESPACE_BEGIN

struct ElementNotFound : std::exception {};

template <class Container, class Element>
inline Element& find(Container& c, const Element& element) throw(ElementNotFound)
{
    const typename Container::iterator it = find(c.begin(), c.end(), element);
    if (it == c.end())
        throw ElementNotFound();
    else
        return *it;
}

template <class Container, class Element>
inline const Element& find(const Container& c, const Element& element) throw(ElementNotFound)
{
    const typename Container::const_iterator it = find(c.begin(), c.end(), element);
    if (it == c.end())
        throw ElementNotFound();
    else
        return *it;
}

template <class Key, class T, class Comp, class Alloc, class Key2>
inline T& find(std::map<Key, T, Comp, Alloc>& m, const Key2& key) throw(ElementNotFound)
{
    const typename std::map<Key, T, Comp, Alloc>::iterator it = m.find(key);
    if (it == m.end())
        throw ElementNotFound();
    else
        return it->second;
}

template <class Key, class T, class Comp, class Alloc, class Key2>
inline const T& find(const std::map<Key, T, Comp, Alloc>& m, const Key2& key) throw(ElementNotFound)
{
    const typename std::map<Key, T, Comp, Alloc>::const_iterator it = m.find(key);
    if (it == m.end())
        throw ElementNotFound();
    else
        return it->second;
}

/* find, nothrow versions */
template <class Container, class Element>
inline Element* find(Container& c, const Element& element, const std::nothrow_t&)
{
    const typename Container::iterator it = find(c.begin(), c.end(), element);
    if (it == c.end())
        return NULL;
    else
        return *it;
}

template <class Container, class Element>
inline const Element* find(const Container& c, const Element& element, const std::nothrow_t&)
{
    const typename Container::const_iterator it = find(c.begin(), c.end(), element);
    if (it == c.end())
        return NULL;
    else
        return *it;
}

template <class Key, class T, class Comp, class Alloc, class Key2>
inline T* find(std::map<Key, T*, Comp, Alloc>& m, const Key2& key, const std::nothrow_t&)
{
    const typename std::map<Key, T*, Comp, Alloc>::iterator it = m.find(key);
    if (it == m.end())
        return NULL;
    else
        return it->second;
}

template <class Key, class T, class Comp, class Alloc, class Key2>
inline const T* find(const std::map<Key, T*, Comp, Alloc>& m, const Key2& key, const std::nothrow_t&)
{
    const typename std::map<Key, T*, Comp, Alloc>::const_iterator it = m.find(key);
    if (it == m.end())
        return NULL;
    else
        return it->second;
}

/* contains(): generic form */
template <class Container, class Element>
inline bool contains(const Container& c, const Element& element)
{
    try
    {
        find(c, element);
        return true;
    }
    catch (ElementNotFound)
    {
        return false;
    }
}

/* contains specializations */
template <class Element>
inline bool contains(const std::vector<Element>& v, const Element& element)
{
    return find(v.begin(), v.end(), element) != v.end();
}

template <class Element>
inline bool contains(const std::list<Element>& l, const Element& element)
{
    return find(l.begin(), l.end(), element) != l.end();
}

template <class Key, class T, class Comp, class Alloc, class Key2>
inline bool contains(const std::map<Key, T, Comp, Alloc>& m, const Key2& key)
{
    return m.count(key) > 0;
}

template <class Key, class Comp, class Alloc, class Key2>
inline bool contains(const std::set<Key, Comp, Alloc>& s, const Key2& key)
{
    return s.count(key) > 0;
}

// ------------ Insertion Utilities

/* This works for vectors and lists */
template <class Container, class ElementType>
inline void insert_into(Container& cont, const ElementType& element)
{
    cont.push_back(element);
}

/* This works for sets */
template<class ElementType, class Comp, class Alloc>
inline void insert_into(std::set<ElementType, Comp, Alloc>& cont, const ElementType& element)
{
    cont.insert(element);
}

/* This works for Ranker */
template <class T, SameValueBehavior Behavior, class Comp>
inline void insert_into(Ranker<T, Behavior, Comp>& cont, const T& element)
{
    cont.insert(element);
}

/* This works for Queue */
template <class ElementType>
inline void insert_into(std::queue<ElementType>& cont, const ElementType& element)
{
    cont.push(element);
}

//------------ Remove first Utilities

/* This works for Ranker */
template <class T, SameValueBehavior Behavior, class Comp>
inline bool remove_first_from(Ranker<T, Behavior, Comp>& cont, const T& element)
{
    const typename Ranker<T, Behavior, Comp>::const_iterator it = find(cont.begin(), cont.end(), element);
    const bool result(it != cont.end());
    if (result) cont.remove_first(element);
    return result;
}

/* This works for vectors and lists */
template <class Container>
inline bool remove_first_from(Container& cont, const typename Container::value_type& element)
{
    const typename Container::iterator it = find(cont.begin(), cont.end(), element);
    const bool result(it != cont.end());
    if (result) cont.erase(it);
    return result;
}

/* This works for sets */
template<class ElementType, class Comp, class Alloc>
inline bool remove_first_from(std::set<ElementType, Comp, Alloc>& cont, const ElementType& element)
{
    return (cont.erase(element) > 0);
}

/* This works for Maps */
template <class Key, class T, class Comp, class Alloc, class ElementType>
inline bool remove_first_from(std::map<Key, T, Comp, Alloc>& m, const ElementType& element)
{
    typename std::map<Key, T, Comp, Alloc>::iterator it = m.begin();
    while (it != m.end())
    {
        if (it->second == element)
        {
            m.erase(it);
            return true;
        }
        ++it;
    }
    return false;
}

//------------ Remove all Utilities

/* This works for Non-associative containers */
template <class T, class Alloc, template <class, class> class Container >
inline bool remove_all_from(Container<T, Alloc>& cont, const typename Container<T, Alloc>::value_type& element)
{
    typename Container<T, Alloc>::iterator it = cont.begin();
    bool result(false);

    while (it != cont.end())
    {
        if (*it == element)
        {
            it = cont.erase(it);
            result = true;
        }
        else
        {
            ++it;
        }
    }
    return result;
}

/* This works for Sets */
template<class ElementType, class Comp, class Alloc>
inline bool remove_all_from(std::set<ElementType, Comp, Alloc>& cont, const ElementType& element)
{
    return remove_first_from(cont, element);
}

/* This works for Maps */
template <class Key, class T, class Comp, class Alloc, class ElementType>
inline bool remove_all_from(std::map<Key, T, Comp, Alloc>& m, const ElementType& element)
{
    typename std::map<Key, T, Comp, Alloc>::iterator it = m.begin();
    bool result(false);
    while (it != m.end())
    {
        if (it->second == element)
        {
            typename std::map<Key, T, Comp, Alloc>::iterator it_temp(it);
            ++it_temp;
            m.erase(it);
            it = it_temp;
            result = true;
        }
        else
        {
            ++it;
        }
    }
    return result;
}

/* This works for Ranker */
template <class T, SameValueBehavior Behavior, class Comp>
inline bool remove_all_from(Ranker<T, Behavior, Comp>& cont, const T& element)
{
    const typename Ranker<T, Behavior, Comp>::const_iterator it = find(cont.begin(), cont.end(), element);
    const bool result(it != cont.end());
    if (result) cont.remove_all(element);
    return result;
}

// Generic container
template <class T>
struct ContainerAdapter
{
    virtual void insert(const T& element) = 0;
    virtual void clear() = 0;
    virtual ~ContainerAdapter() {}
};

template <class T, class Impl>
class ContainerAdapterImpl : public ContainerAdapter<T>
{
    Impl& container;
    virtual void insert(const T& element)
    {
        insert_into(container, element);
    }

    virtual void clear()
    {
        container.clear();
    }
public:
    ContainerAdapterImpl(Impl& cont)
        : container(cont)
    {}
};

template <class Impl>
inline ContainerAdapterImpl<typename Impl::value_type, Impl> containerAdapter(Impl& container)
{
    return ContainerAdapterImpl<typename Impl::value_type, Impl>(container);
}

// CopyContainer -----------------------------
template <class C1, class C2>
static inline void copy_container(const C1& c1, C2& c2)
{
    std::copy(c1.begin(), c1.end(), std::back_insert_iterator<C2> (c2));
}

// TODO: Add more containers.

// Autonomous iterators ----------------------
template <class Container, class Iterator, class Parent>
class AutonomousIteratorBase
{
protected:
    Iterator _current;
    Container& _cont;

    AutonomousIteratorBase(Container& cont, const Iterator& current)
        : _current(current), _cont(cont)
    {}

    AutonomousIteratorBase(Container& cont)
        : _current(cont.begin()), _cont(cont)
    {}

    AutonomousIteratorBase(const AutonomousIteratorBase<Container, Iterator, Parent>& other)
        : _current(other._current), _cont(other._cont)
    {}

    Parent& ThisRef()
    {
        return static_cast<Parent&>(*this);
    }

    const Parent& ThisRef() const
    {
        return static_cast<const Parent&>(*this);
    }
public:
    typedef typename Container::value_type value_type;
    typedef typename Container::reference reference;

    Parent& operator ++()
    {
        ++_current;
        return ThisRef();
    }

    Parent operator ++(int)
    {
        const Parent ret(ThisRef());
        ++(*this);
        return ret;
    }

    Parent& operator --()
    {
        --_current;
        return ThisRef();
    }

    Parent operator --(int)
    {
        const Parent ret(ThisRef());
        --(*this);
        return ret;
    }

    bool operator == (const AutonomousIteratorBase<Container, Iterator, Parent>& other) const
    {
        return _current == other._current;
    }

    typename Container::const_reference operator*() const
    {
        return *_current;
    }

    typename Container::const_iterator& operator->()
    {
        return _current;
    }

    const typename Container::const_iterator& operator->() const
    {
        return _current;
    }

    bool end() const
    {
        return _current == _cont.end();
    }
};

template <class Container>
class AutonomousIterator : public AutonomousIteratorBase<Container, typename Container::iterator, AutonomousIterator<Container> >
{
    typedef AutonomousIteratorBase<Container, typename Container::iterator, AutonomousIterator<Container> > Base;
public:
    AutonomousIterator(const AutonomousIterator<Container>& other)
        : Base(other)
    {}

    AutonomousIterator(Container& cont)
        : Base(cont)
    {}

    AutonomousIterator(Container& cont, typename Container::iterator it)
        : Base(cont, it)
    {}

    typename Container::reference operator*()
    {
        return *this->_current;
    }

    typename Container::iterator& operator->()
    {
        return this->_current;
    }
};

template <class Container>
class CAutonomousIterator : public AutonomousIteratorBase<const Container, typename Container::const_iterator, CAutonomousIterator<Container> >
{
    typedef AutonomousIteratorBase<const Container, typename Container::const_iterator, CAutonomousIterator<Container> > Base;
public:
    CAutonomousIterator(const CAutonomousIterator<Container>& other)
        : Base(other)
    {}

    CAutonomousIterator(const Container& cont)
        : Base(cont)
    {}

    CAutonomousIterator(const Container& cont, typename Container::const_iterator it)
        : Base(cont, it)
    {}
};

NAMESPACE_END

#endif
