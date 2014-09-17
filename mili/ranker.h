/*
Ranker: A minimal library that implements a ranking of elements.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Ezequiel S. Velez
                  Daniel Gutson, Emmanuel Teisaire, FuDePAN 2010
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

#ifndef RANKER_H
#define RANKER_H

#include <list>
#include <set>
#include <map>
#include <iterator>
#include <algorithm>
#include <functional>
#include <utility>
#include "metaprogramming_utils.h"

NAMESPACE_BEGIN

/* to do when you insert an existing value */
enum SameValueBehavior
{
    AddBeforeEqual,
    AddAfterEqual
};

/* This value disables the DisposalPolicy */
enum _NoDisposalPolicy
{
    NoDisposalPolicy
};

template<class T>
struct DisposalNullPolicy
{
    static void destroy(const T& /*element*/)
    {}
};

template<class T>
struct DisposalDeletePolicy
{
    static void destroy(const T& element)
    {
        delete element;
    }
};

template < class T, SameValueBehavior Behavior = AddAfterEqual,
         class Comp = std::less<T>,
         class DisposalPolicy = DisposalNullPolicy<T> >
class Ranker
{
protected:
    typedef std::list<T> Ranking;
    typedef typename Ranking::iterator iterator;

    Ranking ranking;                           /* Container. */
    const size_t TOP;                          /* Maximum number of elements.*/

public:
    /* typedef to simulate STL */
    typedef typename Ranking::const_iterator const_iterator;
    typedef typename Ranking::value_type value_type;
    typedef typename Ranking::reference reference;
    typedef typename Ranking::const_reference const_reference;

    /* Constructor */
    Ranker(size_t top) :
        ranking(),
        TOP(top)
    {}

    /* Member: */

    /* Inserts the element. */
    inline bool insert(const T& element);
    /* Removes the first occurrence of element. */
    inline void remove_first(const T& element);
    /* Removes all occurrences of element. */
    inline void remove_all(const T& element);
    /* Removes the first occurrence of element. */
    inline void remove_first(T* element);
    /* Removes all occurrences of element. */
    inline void remove_all(T* element);
    /* Removes the first occurrence of element without applying the DisposalPolicy. */
    inline void remove_first(const T& element, _NoDisposalPolicy);
    /* Removes all occurrences of element without applying the DisposalPolicy. */
    inline void remove_all(const T& element, _NoDisposalPolicy);
    /* Removes the first occurrence of element without applying the DisposalPolicy. */
    inline void remove_first(T* element, _NoDisposalPolicy);
    /* Removes all occurrences of element without applying the DisposalPolicy. */
    inline void remove_all(T* element, _NoDisposalPolicy);
    /* Erases all of the elements. */
    inline void clear();
    /* True if the Ranker is empty. */
    inline bool empty() const;
    /* Returns the size of the Ranker. */
    inline size_t size() const;
    /* Returns a const_iterator pointing to the beginning of the Ranker. */
    inline const_iterator begin() const;
    /* Returns a const_iterator pointing to the end of the Ranker. */
    inline const_iterator end() const;
    /* Returns the top element. */
    inline const T& top() const;
    /* Returns the bottom element. */
    inline const T& bottom() const;

    ~Ranker()
    {
        iterator it = ranking.begin();
        while (it != ranking.end())
        {
            DisposalPolicy::destroy(*it);
            ++it;
        }
    }
};

//---------------- Unique Ranker --------------------
/*
  T:       type to be rank.
  Comp:    functor to compare the elements values.
  CompEq:  functor to compare the elements.
  DisposalPolicy: functor to delete an element.
*/

template < class T, class Comp, class CompEq, class DisposalPolicy>
class BaseUniqueRanker
{

protected:

    typedef std::multiset<T, Comp> Ranking;
    typedef typename Ranking::iterator iterator;

    typedef std::map<T, iterator, CompEq> Unique;
    typedef typename Unique::iterator uiterator;

    size_t   TOP;
    Unique   unique;
    Ranking  ranking;

public:
    /* typedef to simulate STL */
    typedef typename Ranking::const_iterator const_iterator;
    typedef typename Ranking::value_type value_type;
    typedef typename Ranking::reference reference;
    typedef typename Ranking::const_reference const_reference;

    BaseUniqueRanker(const size_t top) :
        TOP(top)
    {}

    ~BaseUniqueRanker()
    {
        uiterator it = unique.begin();
        while (it != unique.end())
        {
            DisposalPolicy::destroy(it->first);
            ++it;
        }
    }

    /* Members */
    /* Removes the first occurrence of element. */
    inline void remove(const T& element);
    /* Removes the first occurrence of element. */
    inline void remove(T* element);
    /* Removes the first occurrence of element without applying the DisposalPolicy. */
    inline void remove(const T& element, _NoDisposalPolicy);
    /* Removes the first occurrence of element without applying the DisposalPolicy. */
    inline void remove(T* element, _NoDisposalPolicy);
    /* Erases all of the elements. */
    inline void clear();
    /* True if the Unique Ranker is empty. */
    inline bool empty() const;
    /* Returns the size of the Unique Ranker. */
    inline size_t size() const;
    /* Returns a const_iterator pointing to the beginning of the Unique Ranker. */
    inline const_iterator begin() const;
    /* Returns a const_iterator pointing to the end of the Unique Ranker. */
    inline const_iterator end() const;
    /* Returns the top element. */
    inline const T& top() const;
    /* Returns the bottom element. */
    inline const T& bottom() const;
};


template < class T,
         class Comp = std::less<T>,
         class CompEq = std::less<T>,
         class DisposalPolicy = DisposalNullPolicy<T> >
class UniqueRanker : public BaseUniqueRanker<T, Comp, CompEq, DisposalPolicy>
{
    typedef BaseUniqueRanker<T, Comp, CompEq, DisposalPolicy> Parent;
    typedef typename Parent::iterator iterator;
    typedef typename Parent::Ranking Ranking;
    typedef typename Parent::uiterator uiterator;
protected:
    using Parent::ranking;
    using Parent::TOP;
    using Parent::unique;
public:
    UniqueRanker(const size_t top) :
        Parent(top)
    {}
    /* Inserts the element. */
    inline bool insert(const T& element);
};

/*---------------------------------------------------------------*/

template<class T>
struct DummyComparator
{
    bool operator()(typename ParameterType<T>::type, typename ParameterType<T>::type)
    {
        return true;
    }
};

template < class T, class Comp = std::less<T>, class DisposalPolicy = DisposalNullPolicy<T> >

class UniqueRankerLineal : public BaseUniqueRanker<T, Comp, DummyComparator<T>, DisposalPolicy>
{
    typedef BaseUniqueRanker<T, Comp, DummyComparator<T>, DisposalPolicy> Parent;
    typedef typename Parent::Ranking Ranking;
    typedef typename Parent::iterator iterator;

protected:
    using Parent::ranking;
    using Parent::TOP;
public:
    UniqueRankerLineal(const size_t top) :
        Parent(top)
    {}

    /* Inserts the element. */
    inline bool insert(const T& element);
};

#define RANKER_INLINE_H
#include "ranker_inline.h"
#undef RANKER_INLINE_H

NAMESPACE_END
#endif

