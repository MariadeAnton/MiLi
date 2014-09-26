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

#ifndef RANKER_INLINE_H
#error Internal header file, DO NOT include this.
#endif

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline bool Ranker<T, Behavior, Comp, DisposalPolicy>::insert(const T& element)
{
    const std::pair<iterator, iterator> position = equal_range(ranking.begin(), ranking.end(), element, Comp());
    const bool top_reached(ranking.size() >= TOP);
    bool success(true);
    iterator pos;

    if (Behavior == AddBeforeEqual)
        pos = position.first;
    else
        pos = position.second;

    ranking.insert(pos, element);
    const iterator bottom_element = --ranking.end();

    if (top_reached)
    {
        success = (pos != ranking.end());
        DisposalPolicy::destroy(*bottom_element);
        ranking.erase(bottom_element);
    }
    return success;
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline void Ranker<T, Behavior, Comp, DisposalPolicy>::remove_first(const T& element)
{
    const iterator pos = find(ranking.begin(), ranking.end(), element);
    if (pos != ranking.end())
    {
        DisposalPolicy::destroy(*pos);
        ranking.erase(pos);
    }
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline void Ranker<T, Behavior, Comp, DisposalPolicy>::remove_all(const T& element)
{
    iterator it = ranking.begin();
    while (it != ranking.end())
    {
        if (element == *it)
            DisposalPolicy::destroy(*it);
        ++it;
    }
    ranking.remove(element);
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline void Ranker<T, Behavior, Comp, DisposalPolicy>::remove_first(T* element)
{
    const iterator pos = find(ranking.begin(), ranking.end(), *element);
    if (pos != ranking.end())
    {
        DisposalPolicy::destroy(*element);
        ranking.erase(pos);
    }
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline void Ranker<T, Behavior, Comp, DisposalPolicy>::remove_all(T* element)
{
    iterator it = ranking.begin();
    while (it != ranking.end())
    {
        if (*element == *it)
            DisposalPolicy::destroy(*it);
        ++it;
    }
    ranking.remove(*element);
}

/* version which does not apply DisposalPolicy */
template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline void Ranker<T, Behavior, Comp, DisposalPolicy>::remove_first(const T& element, _NoDisposalPolicy)
{
    const iterator pos = find(ranking.begin(), ranking.end(), element);
    if (pos != ranking.end())
    {
        ranking.erase(pos);
    }
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline void Ranker<T, Behavior, Comp, DisposalPolicy>::remove_all(const T& element, _NoDisposalPolicy)
{
    ranking.remove(element);
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline void Ranker<T, Behavior, Comp, DisposalPolicy>::remove_first(T* element, _NoDisposalPolicy)
{
    const iterator pos = find(ranking.begin(), ranking.end(), *element);
    if (pos != ranking.end())
    {
        ranking.erase(pos);
    }
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline void Ranker<T, Behavior, Comp, DisposalPolicy>::remove_all(T* element, _NoDisposalPolicy)
{
    ranking.remove(*element);
}

/*---------------------------------------------------------------*/
template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline bool Ranker<T, Behavior, Comp, DisposalPolicy>::empty() const
{
    return ranking.empty();
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline size_t Ranker<T, Behavior, Comp, DisposalPolicy>::size() const
{
    return ranking.size();
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline void Ranker<T, Behavior, Comp, DisposalPolicy>::clear()
{
    iterator it = ranking.begin();
    while (it != ranking.end())
    {
        DisposalPolicy::destroy(*it);
        ++it;
    }
    ranking.clear();
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline typename Ranker<T, Behavior, Comp, DisposalPolicy>::const_iterator Ranker<T, Behavior, Comp, DisposalPolicy>::begin() const
{
    return ranking.begin();
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline typename Ranker<T, Behavior, Comp, DisposalPolicy>::const_iterator Ranker<T, Behavior, Comp, DisposalPolicy>::end() const
{
    return ranking.end();
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline const T& Ranker<T, Behavior, Comp, DisposalPolicy>::top() const
{
    return *(ranking.begin());
}

template<class T, SameValueBehavior Behavior, class Comp, class DisposalPolicy>
inline const T& Ranker<T, Behavior, Comp, DisposalPolicy>::bottom() const
{
    return *(--ranking.end());
}

/* Complexity: Logarithmic */
template<class T, class Comp, class CompEq, class DisposalPolicy>
inline bool UniqueRanker<T, Comp, CompEq, DisposalPolicy>::insert(const T& element)
{
    const iterator rankPos = ranking.insert(element);
    const std::pair<uiterator, bool> aux = unique.insert(std::pair<T, iterator>(element, rankPos));
    bool success(true);
    const iterator bottom_element = --ranking.end();

    if (aux.second)                                           // It is new
    {
        if (ranking.size() > TOP)
        {
            const T bottom = *bottom_element;
            unique.erase(*bottom_element);                 // Remove the last one
            ranking.erase(bottom_element);
            success = (rankPos != bottom_element);
            DisposalPolicy::destroy(bottom);
        }
    }
    else                                                      // Already exist
    {
        if (Comp()(element, (aux.first)->first))              // The new one is better
        {
            const T old = *((aux.first)->second);
            ranking.erase((aux.first)->second);
            unique.erase(aux.first);                          // Remove the old one
            unique.insert(std::pair<T, iterator>(element, rankPos));
            DisposalPolicy::destroy(old);
        }
        else                                                  // The old one is better
        {
            ranking.erase(rankPos);
            DisposalPolicy::destroy(element);
            success = false;
        }
    }
    return success;
}

template<class T, class Comp, class CompEq, class DisposalPolicy>
inline void BaseUniqueRanker<T, Comp, CompEq, DisposalPolicy>::remove(const T& element)
{
    const uiterator pos = unique.find(element);
    if (pos != unique.end())
    {
        DisposalPolicy::destroy(pos->first);
        ranking.erase(pos->second);
        unique.erase(pos);
    }
}

template<class T, class Comp, class CompEq, class DisposalPolicy>
inline void BaseUniqueRanker<T, Comp, CompEq, DisposalPolicy>::remove(T* element)
{
    const uiterator pos = unique.find(*element);
    if (pos != unique.end())
    {
        DisposalPolicy::destroy(pos->first);
        ranking.erase(pos->second);
        unique.erase(pos);
    }
}

/* version which does not apply DisposalPolicy */
template<class T, class Comp, class CompEq, class DisposalPolicy>
inline void BaseUniqueRanker<T, Comp, CompEq, DisposalPolicy>::remove(const T& element, _NoDisposalPolicy)
{
    const uiterator pos = unique.find(element);
    if (pos != unique.end())
    {
        ranking.erase(pos->second);
        unique.erase(pos);
    }
}

template<class T, class Comp, class CompEq, class DisposalPolicy>
inline void BaseUniqueRanker<T, Comp, CompEq, DisposalPolicy>::remove(T* element, _NoDisposalPolicy)
{
    const uiterator pos = unique.find(*element);
    if (pos != unique.end())
    {
        ranking.erase(pos->second);
        unique.erase(pos);
    }
}

/*---------------------------------------------------------------*/

template<class T, class Comp, class CompEq, class DisposalPolicy>
inline bool BaseUniqueRanker<T, Comp, CompEq, DisposalPolicy>::empty() const
{
    return ranking.empty();
}

template<class T, class Comp, class CompEq, class DisposalPolicy>
inline size_t BaseUniqueRanker<T, Comp, CompEq, DisposalPolicy>::size() const
{
    return ranking.size();
}

template<class T, class Comp, class CompEq, class DisposalPolicy>
inline void BaseUniqueRanker<T, Comp, CompEq, DisposalPolicy>::clear()
{
    uiterator it = unique.begin();
    while (it != unique.end())
    {
        DisposalPolicy::destroy(it->first);
        ++it;
    }
    unique.clear();
    ranking.clear();
}

template<class T, class Comp, class CompEq, class DisposalPolicy>
inline typename BaseUniqueRanker<T, Comp, CompEq, DisposalPolicy>::const_iterator BaseUniqueRanker<T, Comp, CompEq, DisposalPolicy>::begin() const
{
    return ranking.begin();
}

template<class T, class Comp, class CompEq, class DisposalPolicy>
inline typename BaseUniqueRanker<T, Comp, CompEq, DisposalPolicy>::const_iterator BaseUniqueRanker<T, Comp, CompEq, DisposalPolicy>::end() const
{
    return ranking.end();
}

template<class T, class Comp, class CompEq, class DisposalPolicy>
inline const T& BaseUniqueRanker<T, Comp, CompEq, DisposalPolicy>::top() const
{
    return *(ranking.begin());
}

template<class T, class Comp, class CompEq, class DisposalPolicy>
inline const T& BaseUniqueRanker<T, Comp, CompEq, DisposalPolicy>::bottom() const
{
    return *(--ranking.end());
}

/* Complexity: Lineal */
template<class T, class Comp, class DisposalPolicy>
inline bool UniqueRankerLineal<T, Comp, DisposalPolicy>::insert(const T& element)
{
    const iterator prevElement = std::find(ranking.begin(), ranking.end(), element);

    bool success(true);
    if (prevElement == ranking.end()) // It is new
    {
        const iterator rankPos = ranking.insert(element);

        if (ranking.size() > TOP)
        {
            const iterator bottom_element = --ranking.end();
            ranking.erase(bottom_element); // Remove the last one
            success = (rankPos != bottom_element);
        }
    }
    else
    {
        if (Comp()(element, *prevElement)) // The new one is better
        {
            ranking.erase(prevElement);    // Remove the old one
            ranking.insert(element);
        }
        else                               // The old one is better
        {
            success = false;
        }
    }
    return success;
}

