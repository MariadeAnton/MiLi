/*
example_ranker: An example that uses MiLi's Ranker.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Ezequiel S. Velez, FuDePAN 2010
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

    This is an example file.
*/

#include <iostream>
#include "mili/mili.h"

using namespace mili;
using namespace std;

template <class T>
void print(CAutonomousIterator<T> it)
{
    while (!it.end())
    {
        cout << *it << endl;
        ++it;
    }
}
//------------------------------

struct Player
{
    string name;
    float  score;

    Player(string name, float score): name(name), score(score)
    {}

    void print() const
    {
        cout << name << " - " << score << endl;
    }
};

/* Compare two Players' names */
struct PlayerUnique
{
    bool operator()(const Player& p1, const Player& p2)
    {
        return p1.name < p2.name;
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

typedef UniqueRanker<Player, PlayerRanking, PlayerUnique> PlayersRanking;

void print_classes(CAutonomousIterator<PlayersRanking> it)
{
    while (!it.end())
    {
        it->print();
        ++it;
    }
    cout << "_______________________" << endl;
}

void unique_ranker_test()
{
    PlayersRanking UR(5);

    cout << UR.insert(Player("Umpa lumpa A", .1)) << endl;
    cout << UR.insert(Player("Umpa lumpa B", .3)) << endl;
    cout << UR.insert(Player("Umpa lumpa C", .3)) << endl;
    cout << UR.insert(Player("Umpa lumpa B", .2)) << endl;
    cout << UR.insert(Player("Umpa lumpa D", .5)) << endl;
    cout << UR.insert(Player("Umpa lumpa E", .6)) << endl;
    cout << UR.insert(Player("Umpa lumpa B", .5)) << endl;
    cout << UR.insert(Player("Umpa lumpa F", .8)) << endl;

    CAutonomousIterator<PlayersRanking> it(UR);
    print_classes(it);

    UR.top().print();                     // Print the top Umpa Lumpa
    UR.bottom().print();                  // Print the bottom Umpa Lumpa

    cout << "-------- remove Umpa lumpa E --------" << endl;
    UR.remove(Player("Umpa lumpa E", .6));
    CAutonomousIterator<PlayersRanking> it2(UR);
    print_classes(it2);
}


//----------UNIQUE RANKER LINEAL TEST--------------

struct PlayerLineal : Player
{
    PlayerLineal(const string& name, float score): Player(name, score)
    {}

    bool operator == (const Player& aPlayer) const
    {
        return name == aPlayer.name;
    }
};

typedef UniqueRankerLineal<PlayerLineal, PlayerRanking> PlayersRankingLineal;

void print_classes_lineal(CAutonomousIterator<PlayersRankingLineal> it)
{
    while (!it.end())
    {
        it->print();
        ++it;
    }
    cout << "_______________________" << endl;
}

void unique_ranker_lineal_test()
{
    PlayersRankingLineal UR(5);

    cout << UR.insert(PlayerLineal("Umpa lumpa A", .1)) << endl;
    cout << UR.insert(PlayerLineal("Umpa lumpa B", .3)) << endl;
    cout << UR.insert(PlayerLineal("Umpa lumpa C", .3)) << endl;
    cout << UR.insert(PlayerLineal("Umpa lumpa B", .2)) << endl;
    cout << UR.insert(PlayerLineal("Umpa lumpa D", .5)) << endl;
    cout << UR.insert(PlayerLineal("Umpa lumpa E", .6)) << endl;
    cout << UR.insert(PlayerLineal("Umpa lumpa B", .5)) << endl;
    cout << UR.insert(PlayerLineal("Umpa lumpa F", .8)) << endl;

    CAutonomousIterator<PlayersRankingLineal> it(UR);
    print_classes_lineal(it);

    UR.top().print();                     // Print the top Umpa Lumpa
    UR.bottom().print();                  // Print the bottom Umpa Lumpa

    cout << "-------- remove Umpa lumpa E --------" << endl;
    UR.remove(PlayerLineal("Umpa lumpa E", .6));
    CAutonomousIterator<PlayersRankingLineal> it2(UR);
    print_classes_lineal(it2);
}

//-------------------------------------------
typedef Ranker<int, AddBeforeEqual> Ranking;

void ranker_test()
{
    const size_t TOP = 5;
    const int I = -10;
    Ranking R(TOP);

    R.insert(10);
    R.insert(30);
    R.insert(I);
    R.insert(20);
    R.insert(I);

    CAutonomousIterator<Ranking> it(R);
    print<Ranking> (it);

    cout << "-- Insert 0 and 50 --" << endl;
    R.insert(0);
    R.insert(50);

    CAutonomousIterator<Ranking> it1(R);
    print<Ranking> (it1);

    R.remove_all(I);
    cout << "-- Remove All " << I << " --" << endl;

    CAutonomousIterator<Ranking> it2(R);
    print<Ranking> (it2);
    cout << "----- size: " << R.size() << endl;
    cout << "top: " << R.top() << " - bottom: " << R.bottom() << endl;

    if (!R.empty()) R.clear();

    cout << "size after clear: " << R.size() << endl;
}

//------------------------------------------------------
int main()
{
    string test;
    cout << "Indicate which library you want to test. (R = Ranker ; UR = Unique Ranker ; URL = Unique Ranker Lineal):" << endl;
    cin >> test;

    if (test == "R")
        ranker_test();
    else if (test == "UR")
        unique_ranker_test();
    else if (test == "URL")
        unique_ranker_lineal_test();
    else
        cout << "Error: you must choose R, UR or URL" << endl;
    return 0;
}

