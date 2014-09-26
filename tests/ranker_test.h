/*
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Hugo Arregui, Emmanuel Teisaire, FuDePAN 2011
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

    This is a test file.

*/

#include "google/gtest/gtest.h"
#include "google/gmock/gmock.h"
#include "mili/mili.h"

using std::string;
using namespace mili;

struct Player
{
    string name;
    float  score;

    Player(string name, float score)
        : name(name),
          score(score)
    {}

    bool operator==(const Player& aPlayer) const
    {
        return name == aPlayer.name;
    }
};

/* Compare two Players' names */
struct PlayerUnique
{
    bool operator()(const Player& p1, const Player& p2)
    {
        return p1.name > p2.name;
    }
};

/* Compare two Players' scores */
struct PlayerRanking
{
    bool operator()(const Player& p1, const Player& p2)
    {
        return p1.score > p2.score;
    }
};

template <class T>
struct PlayerPointerAdapter
{
    bool operator()(const Player* const p1, const Player* const p2)
    {
        T c;
        return p1 != NULL && p2 != NULL && c.operator()(*p1, *p2);
    }
};

template <class ScoreT, class T>
struct GetScore
{};

template<class T, class Iterator>
bool isSorted(Iterator it)
{
    GetScore<T, Iterator> f;
    bool sorted = true;
    T score = f(it);
    while (!it.end() && sorted)
    {
        sorted = (score >= f(it));
        score = f(it);
        ++it;
    }
    return sorted;
}

