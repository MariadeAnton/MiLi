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

#include "ranker_test.h"

typedef UniqueRanker<Player, PlayerRanking, PlayerUnique> PlayersRanking;
typedef CAutonomousIterator<PlayersRanking> PlayersRankingIterator;

typedef UniqueRanker < Player*, PlayerPointerAdapter<PlayerRanking>, PlayerPointerAdapter<PlayerUnique>,
        DisposalDeletePolicy<Player*> > PointerPlayersUniqueRanking;
typedef CAutonomousIterator<PointerPlayersUniqueRanking> PointerPlayersUniqueRankingIterator;

template <>
struct GetScore<float, PlayersRankingIterator>
{
    float operator()(const PlayersRankingIterator& it)
    {
        return it->score;
    }
};

template <>
struct GetScore<float, PointerPlayersUniqueRankingIterator>
{
    float operator()(const PointerPlayersUniqueRankingIterator& it)
    {
        return (*it)->score;
    }
};

TEST(UniqueRankerTest, test_delete_disposal)
{
    PointerPlayersUniqueRanking UR(5);

    ASSERT_TRUE(UR.insert(new Player("Umpa lumpa A", .1)));
    ASSERT_TRUE(UR.insert(new Player("Umpa lumpa B", .3)));
    ASSERT_TRUE(UR.insert(new Player("Umpa lumpa C", .3)));
    ASSERT_FALSE(UR.insert(new Player("Umpa lumpa B", .2)));
    ASSERT_TRUE(UR.insert(new Player("Umpa lumpa D", .5)));
    ASSERT_TRUE(UR.insert(new Player("Umpa lumpa E", .6)));
    ASSERT_TRUE(UR.insert(new Player("Umpa lumpa B", .5)));
    ASSERT_TRUE(UR.insert(new Player("Umpa lumpa F", .8)));

    PointerPlayersUniqueRankingIterator it(UR);
    ASSERT_TRUE((isSorted<float, PointerPlayersUniqueRankingIterator>(it)));

    ASSERT_EQ("Umpa lumpa F", UR.top()->name);
    ASSERT_EQ("Umpa lumpa C", UR.bottom()->name);

    Player* p = new Player("Umpa lumpa E", .6);
    UR.remove(p);
    delete p;
    PointerPlayersUniqueRankingIterator it2(UR);
    ASSERT_TRUE((isSorted<float, PointerPlayersUniqueRankingIterator>(it2)));
}

TEST(UniqueRankerTest, test_pointer)
{
    PlayersRanking UR(5);

    ASSERT_TRUE(UR.insert(Player("Umpa lumpa A", .1)));
    ASSERT_TRUE(UR.insert(Player("Umpa lumpa B", .3)));
    ASSERT_TRUE(UR.insert(Player("Umpa lumpa C", .3)));
    ASSERT_FALSE(UR.insert(Player("Umpa lumpa B", .2)));
    ASSERT_TRUE(UR.insert(Player("Umpa lumpa D", .5)));
    ASSERT_TRUE(UR.insert(Player("Umpa lumpa E", .6)));
    ASSERT_TRUE(UR.insert(Player("Umpa lumpa B", .5)));
    ASSERT_TRUE(UR.insert(Player("Umpa lumpa F", .8)));

    PlayersRankingIterator it(UR);
    ASSERT_TRUE((isSorted<float, PlayersRankingIterator>(it)));

    ASSERT_EQ("Umpa lumpa F", UR.top().name);
    ASSERT_EQ("Umpa lumpa C", UR.bottom().name);

    UR.remove(Player("Umpa lumpa E", .6));
    PlayersRankingIterator it2(UR);
    ASSERT_TRUE((isSorted<float, PlayersRankingIterator>(it2)));
}

typedef Ranker<int, AddBeforeEqual> Ranking;
typedef CAutonomousIterator<Ranking> RankingIterator;

typedef Ranker<int*, AddBeforeEqual, std::less<int*>, DisposalDeletePolicy<int*> > PointerRanking;
typedef CAutonomousIterator<PointerRanking> PointerRankingIterator;

template<>
struct GetScore<int, RankingIterator>
{
    int operator()(const RankingIterator& it)
    {
        return *it;
    }
};

TEST(RankerTest, test)
{
    const size_t TOP = 5;
    const int I = -10;
    Ranking R(TOP);

    R.insert(10);
    R.insert(30);
    R.insert(I);
    R.insert(20);
    R.insert(I);

    RankingIterator it(R);
    isSorted<int, RankingIterator>(it);

    R.insert(0);
    R.insert(50);
    RankingIterator it1(R);
    isSorted<int, RankingIterator>(it1);

    R.remove_all(I);
    RankingIterator it2(R);
    isSorted<int, RankingIterator>(it2);

    ASSERT_EQ(3, R.size());
    ASSERT_EQ(0, R.top());
    ASSERT_EQ(20, R.bottom());

    R.clear();
    ASSERT_EQ(0, R.size());
}

TEST(RankerTest, test_delete_disposal)
{
    PointerRanking UR(2);

    Randomizer<int> r(0, 1000, 0);
    for (unsigned int i = 0; i < 10000; ++i)
    {
        UR.insert(new int(r.get()));
    }
}

typedef UniqueRankerLineal<Player, PlayerRanking> PlayersRankingLineal;
typedef CAutonomousIterator<PlayersRankingLineal> PlayersRankingLinealIterator;

template<>
struct GetScore<float, PlayersRankingLinealIterator>
{
    float operator()(const PlayersRankingLinealIterator& it)
    {
        return it->score;
    }
};

TEST(UniqueRankerLinealTest, test)
{
    PlayersRankingLineal UR(5);

    ASSERT_TRUE(UR.insert(Player("Umpa lumpa A", .1)));
    ASSERT_TRUE(UR.insert(Player("Umpa lumpa B", .3)));
    ASSERT_TRUE(UR.insert(Player("Umpa lumpa C", .3)));
    ASSERT_FALSE(UR.insert(Player("Umpa lumpa B", .2)));
    ASSERT_TRUE(UR.insert(Player("Umpa lumpa D", .5)));
    ASSERT_TRUE(UR.insert(Player("Umpa lumpa E", .6)));
    ASSERT_TRUE(UR.insert(Player("Umpa lumpa B", .5)));
    ASSERT_TRUE(UR.insert(Player("Umpa lumpa F", .8)));

    CAutonomousIterator<PlayersRankingLineal> it(UR);
    ASSERT_TRUE((isSorted<float, PlayersRankingLinealIterator>(it)));

    ASSERT_EQ("Umpa lumpa F", UR.top().name);
    ASSERT_EQ("Umpa lumpa C", UR.bottom().name);

    UR.remove(Player("Umpa lumpa E", .6));
    CAutonomousIterator<PlayersRankingLineal> it2(UR);
    ASSERT_TRUE((isSorted<float, PlayersRankingLinealIterator>(it2)));
}
