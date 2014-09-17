/*
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Lucas Paradisi, Matias Tripode, FuDePAN 2012
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


#include <vector>
#include <set>
#include <list>
#include <string>
#include "google/gtest/gtest.h"
#include "google/gmock/gmock.h"
#include "mili/mili.h"

using namespace mili;

template <typename T>
void assertArrayEquals(const T& a1, const T& a2, unsigned int size)
{
    bool equals = true;
    int i = 0;
    while (i < size && equals)
    {
        equals = (a1[i] == a2[i]);
        ++i;
    }
    ASSERT_TRUE(equals) << "Arrays not equals";
}

std::string get_TypeId(const std::string& s)
{
    uint32_t a = 0;

#if (MILI_COMPILER == MILI_COMPILER_VS)
    s._Copy_s(reinterpret_cast<char*>(&a),sizeof(a),sizeof(a),0);
#else
    s.copy(reinterpret_cast<char*>(&a), sizeof(uint32_t), 0);
#endif

    if ((sizeof(uint32_t) + sizeof(char) * a) <= s.length()) //To avoid exception when non-debug info
        return s.substr(sizeof(uint32_t), sizeof(char) * a);
    else
        return s;
}

struct A
{
    typedef class mili::bostream<mili::DebugPolicyBostream> bostream;
    typedef class mili::bistream<mili::DebugPolicyBistream> bistream;

    unsigned int id;
    std::string name;
    long double a;

    A()
        : id(0), name(), a(0)
    {}

    A(unsigned int Id, const std::string& Name, long double A)
        : id(Id), name(Name), a(A)
    {}

    friend bostream& operator<<(bostream& out, const A& o)
    {
        out << o.id << o.name << o.a;
        return out;
    }

    friend bistream& operator>>(bistream& in, A& o)
    {
        in >> o.id >> o.name >> o.a;
        return in;
    }

    bool operator==(const A& o) const
    {
        return (id == o.id && name == o.name && a == o.a);
    }
};


struct B
{

    typedef class mili::bostream<mili::NoDebugPolicyBostream> bostream;
    typedef class mili::bistream<mili::NoDebugPolicyBistream> bistream;

    unsigned int id;
    std::string name;
    long double b;

    B()
        : id(0), name(), b(0)
    {}

    B(unsigned int Id, const std::string& Name, long double B)
        : id(Id), name(Name), b(B)
    {}

    friend bostream& operator<<(bostream& out, const B& o)
    {
        out << o.id << o.name << o.b;
        return out;
    }

    friend bistream& operator>>(bistream& in, B& o)
    {
        in >> o.id >> o.name >> o.b;
        return in;
    }

    bool operator==(const B& o) const
    {
        return (id == o.id && name == o.name && b == o.b);
    }
};

TEST(BinaryStream, BSTREAMS_DEBUG_identifier_test)
{
    typedef class mili::bostream<mili::DebugPolicyBostream> bostream;
    bostream bos;

    bos << -13;
    ASSERT_EQ(typeid(int).name(), get_TypeId(bos.str()));
    bos.clear();

    bos << 13u;
    ASSERT_EQ(typeid(unsigned int).name(), get_TypeId(bos.str()));
    bos.clear();

    bos << 1.2f;
    ASSERT_EQ(typeid(float).name(), get_TypeId(bos.str()));
    bos.clear();

    bos << 's';
    ASSERT_EQ(typeid(char).name(), get_TypeId(bos.str()));
    bos.clear();

    bos << double(1.22);
    ASSERT_EQ(typeid(double).name(), get_TypeId(bos.str()));
    bos.clear();

    bos << 1.22L;
    ASSERT_EQ(typeid(long double).name(), get_TypeId(bos.str()));
    bos.clear();

    bos << std::string("FuDePAN");
    ASSERT_EQ(typeid(uint32_t).name(), get_TypeId(bos.str()));
    bos.clear();
}

TEST(BinaryStream, BSTREAMS_NO_DEBUG_identifier_test)
{

    typedef class mili::bostream<mili::NoDebugPolicyBostream> bostream;
    bostream bos;

    bos << -13;
    ASSERT_NE(typeid(int).name(), get_TypeId(bos.str()));
    bos.clear();

    bos << 13u;
    ASSERT_NE(typeid(unsigned int).name(), get_TypeId(bos.str()));
    bos.clear();

    bos << 1.2f;
    ASSERT_NE(typeid(float).name(), get_TypeId(bos.str()));
    bos.clear();

    bos << 's';
    ASSERT_NE(typeid(char).name(), get_TypeId(bos.str()));
    bos.clear();

    bos << double(1.22);
    ASSERT_NE(typeid(double).name(), get_TypeId(bos.str()));
    bos.clear();

    bos << 1.22L;
    ASSERT_NE(typeid(long double).name(), get_TypeId(bos.str()));
    bos.clear();

    bos << std::string("FuDePAN");
    ASSERT_NE(typeid(uint32_t).name(), get_TypeId(bos.str()));
    bos.clear();
}


TEST(BinaryStream, BSTREAMS_DEBUG_typemismatch_test)
{
    typedef class mili::bostream<mili::DebugPolicyBostream> bostream;
    typedef class mili::bistream<mili::DebugPolicyBistream> bistream;

    bostream bos;
    const int int_loaded = 3;
    const char char_loaded[] = "e4fry";

    float float_loaded;
    unsigned char uchar_loaded[5];

    bos << int_loaded;
    bistream bis(bos.str());
    ASSERT_THROW(bis >> float_loaded, type_mismatch);

    bos.clear();
    bos << char_loaded;
    bis.str(bos.str());
    ASSERT_THROW(bis >> uchar_loaded, type_mismatch);
}
TEST(BinaryStream, BSTREAMS_NO_DEBUG_typemismatch_test)
{
    typedef class mili::bostream<mili::NoDebugPolicyBostream> bostream;
    typedef class mili::bistream<mili::NoDebugPolicyBistream> bistream;

    bostream bos;
    const int int_loaded = 3;
    const char char_loaded[] = "e4fry";

    float float_loaded;
    unsigned char uchar_loaded[5];

    bos << int_loaded;
    bistream bis(bos.str());


    EXPECT_NO_THROW(bis >> float_loaded);

    bos.clear();
    bos << char_loaded;
    bis.str(bos.str());
    EXPECT_NO_THROW(bis >> uchar_loaded);
}

TEST(BinaryStream, chainedValues_test)
{

    typedef class mili::bostream<mili::DebugPolicyBostream> bostream;
    typedef class mili::bistream<mili::DebugPolicyBistream> bistream;

    bostream bos;

    const float f_original = 1.2f;
    const int i_original = 3;
    const double d_original = 0.89;
    const A a_original(3, "pepe", 43);
    const bool b_original = true;

    bos << f_original << i_original << d_original << a_original << b_original;

    bistream bis(bos.str());
    float f_loaded;
    int i_loaded;
    double d_loaded;
    A a_loaded;
    bool b_loaded;
    bis >> f_loaded >> i_loaded >> d_loaded >> a_loaded >> b_loaded;

    ASSERT_EQ(f_original, f_loaded);
    ASSERT_EQ(i_original, i_loaded);
    ASSERT_EQ(d_original, d_loaded);
    ASSERT_EQ(a_original, a_loaded);
    ASSERT_EQ(b_original, b_loaded);
}

TEST(BinaryStream, chainedValues_No_Debug_test)
{

    typedef class mili::bostream<mili::NoDebugPolicyBostream> bostream;
    typedef class mili::bistream<mili::NoDebugPolicyBistream> bistream;

    bostream bos;

    const float f_original = 1.2f;
    const int i_original = 3;
    const double d_original = 0.89;
    const B b_original(3, "pepe", 43);
    const bool bool_original = true;

    bos << f_original << i_original << d_original << b_original << bool_original;

    bistream bis(bos.str());
    float f_loaded;
    int i_loaded;
    double d_loaded;
    B b_loaded;
    bool bool_loaded;

    bis >> f_loaded >> i_loaded >> d_loaded >> b_loaded >> bool_loaded;

    ASSERT_EQ(f_original, f_loaded);
    ASSERT_EQ(i_original, i_loaded);
    ASSERT_EQ(d_original, d_loaded);
    ASSERT_EQ(b_original, b_loaded);
    ASSERT_EQ(bool_original, bool_loaded);

}

TEST(BinaryStream, contaniers_test)
{

    typedef class mili::bostream<mili::DebugPolicyBostream> bostream;
    typedef class mili::bistream<mili::DebugPolicyBistream> bistream;

    bostream bos;
    std::vector<int> integers_original;
    std::set<float> set_original;
    std::list<char> list_original;
    const double numbers_original[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    insert_into(integers_original, 6);
    insert_into(integers_original, 7);
    insert_into(integers_original, 8);
    insert_into(integers_original, 9);
    insert_into(integers_original, 0);
    insert_into(integers_original, 1);
    insert_into(set_original, 0.1f);
    insert_into(set_original, 1.1f);
    insert_into(set_original, 2.1f);
    insert_into(set_original, 3.1f);
    insert_into(set_original, 4.1f);
    insert_into(list_original, 't');
    insert_into(list_original, 'y');
    insert_into(list_original, 'w');
    insert_into(list_original, 'A');

    bos << integers_original << set_original << list_original << numbers_original;

    std::vector<int> integers_loaded;
    std::set<float> set_loaded;
    std::list<char> list_loaded;
    double numbers_loaded[9];
    bistream bis(bos.str());
    bis >> integers_loaded >> set_loaded >> list_loaded >> numbers_loaded;

    ASSERT_EQ(integers_original, integers_loaded);

    ASSERT_EQ(set_original, set_loaded);

    ASSERT_EQ(list_original, list_loaded);

    /* VC2010 can't resolve automatically the template parameter since
    it could be "const double[9]" (like numbers_original) or 
    "double[9]" (like numbers_loaded). */
    assertArrayEquals<const double[9]>(numbers_original, numbers_loaded, 9);
}

TEST(BinaryStream, No_Debug_Contaniers_Test)
{
    typedef class mili::bostream<mili::NoDebugPolicyBostream> bostream;
    typedef class mili::bistream<mili::NoDebugPolicyBistream> bistream;

    bostream bos;
    std::vector<int> integers_original;
    std::set<float> set_original;
    std::list<char> list_original;
    const double numbers_original[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    insert_into(integers_original, 6);
    insert_into(integers_original, 7);
    insert_into(integers_original, 8);
    insert_into(integers_original, 9);
    insert_into(integers_original, 0);
    insert_into(integers_original, 1);
    insert_into(set_original, 0.1f);
    insert_into(set_original, 1.1f);
    insert_into(set_original, 2.1f);
    insert_into(set_original, 3.1f);
    insert_into(set_original, 4.1f);
    insert_into(list_original, 't');
    insert_into(list_original, 'y');
    insert_into(list_original, 'w');
    insert_into(list_original, 'A');

    bos << integers_original << set_original << list_original << numbers_original;

    std::vector<int> integers_loaded;
    std::set<float> set_loaded;
    std::list<char> list_loaded;
    double numbers_loaded[9];
    bistream bis(bos.str());
    bis >> integers_loaded >> set_loaded >> list_loaded >> numbers_loaded;

    ASSERT_EQ(integers_original, integers_loaded);

    ASSERT_EQ(set_original, set_loaded);

    ASSERT_EQ(list_original, list_loaded);

    /* VC2010 can't resolve automatically the template parameter since
    it could be "const double[9]" (like numbers_original) or 
    "double[9]" (like numbers_loaded). */
    assertArrayEquals<const double[9]>(numbers_original, numbers_loaded, 9);
}
