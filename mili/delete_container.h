/*
delete_container: A minimal library for deleting the objects of a container of pointers.
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

#ifndef DELETE_CONTAINER_H
#define DELETE_CONTAINER_H

#include <algorithm>

NAMESPACE_BEGIN

template <class T>
struct deleter
{
    void operator()(T* tp) const
    {
        delete tp;
    }
};

template <class T>
struct pair_deleter
{
    void operator()(const T& p) const
    {
        delete p.second;
    }
};

/* Non-associative containers */
template <class T, class Alloc, template <class, class> class Container >
inline void delete_container(Container<T*, Alloc>& cont)
{
    for_each(cont.begin(), cont.end(), deleter<T>());
    cont.clear();
}

/* Sets  */
template <class T, class Comp, class Alloc, template <class, class, class> class Container >
inline void delete_container(Container<T*, Comp, Alloc>& cont)
{
    for_each(cont.begin(), cont.end(), deleter<T>());
    cont.clear();
}

/* Associative containers */
template <class Key, class T, class Comp, class Alloc, template <class, class, class, class> class Container >
inline void delete_container(Container<Key, T*, Comp, Alloc>& cont)
{
    for_each(cont.begin(), cont.end(), pair_deleter<typename Container<Key, T*, Comp, Alloc>::value_type >());
    cont.clear();
}

template <class T>
struct vector_deleter
{
    void operator()(T* tp) const
    {
        delete [] tp;
    }
};

template <class T>
struct vector_pair_deleter
{
    void operator()(const T& p) const
    {
        delete [] p.second;
    }
};

template <class T, class Alloc, template <class, class> class Container >
inline void vector_delete_container(Container<T*, Alloc>& cont)
{
    for_each(cont.begin(), cont.end(), vector_deleter<T>());
    cont.clear();
}

/* Sets */
template <class T, class Comp, class Alloc, template <class, class, class> class Container >
inline void vector_delete_container(Container<T*, Comp, Alloc>& cont)
{
    for_each(cont.begin(), cont.end(), vector_deleter<T>());
    cont.clear();
}

/* Associative containers */
template <class Key, class T, class Comp, class Alloc, template <class, class, class, class> class Container >
inline void vector_delete_container(Container<Key, T*, Comp, Alloc>& cont)
{
    for_each(cont.begin(), cont.end(), vector_pair_deleter<typename Container<Key, T*, Comp, Alloc>::value_type >());
    cont.clear();
}

template <class Container>
struct auto_delete_container : public Container
{
    ~auto_delete_container()
    {
        delete_container(static_cast<Container&>(*this));
    }
};

template <class Container>
struct auto_vector_delete_container : public Container
{
    ~auto_vector_delete_container()
    {
        vector_delete_container(static_cast<Container&>(*this));
    }
};

NAMESPACE_END

#endif
