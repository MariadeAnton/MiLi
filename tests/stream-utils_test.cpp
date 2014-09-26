/*
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Hugo Arregui, FuDePAN 2011
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
#include <fstream>
#include "google/gtest/gtest.h"
#include "google/gmock/gmock.h"
#include "mili/mili.h"

using namespace mili;

static void generate_file(const char* name)
{
    std::ofstream f(name);
    std::set<float> v;

    for (int i = 0; i < 10; i++)
    {
        v.clear();
        for (int j = 0; j <= 10; j++)
            insert_into(v, static_cast<float>(j));

        f << v; /* PROVIDED BY MiLi */
        f << std::endl;
    }
}

static void load_file(const char* name)
{
    std::ifstream f(name);
    std::vector<float> v;

    unsigned int i = 0;
    while (f >> v)  /* PROVIDED BY MiLi */
    {
        Separator(v, '\t');  /* PROVIDED BY MiLi */
        for (int j = 0; j < v.size(); j++)
            ASSERT_EQ(v[j], j);
        v.clear();
        ++i;
    }
    ASSERT_EQ(10, i);
}

TEST(StreamUtilsTest, test)
{
    const char file[] = "stream-utils.test";
    generate_file(file);
    load_file(file);
    remove(file);
}

static void generate_file_with_separator(const char* name, char sep)
{
    std::ofstream f(name);
    std::set<float> v;

    _Separator< std::set<float> > s = Separator(v, sep);

    for (int i = 0; i < 10; i++)
    {
        v.clear();
        for (int j = 0; j <= 10; j++)
            insert_into(v, static_cast<float>(j));

        s.v = v;

        f << s ; /* PROVIDED BY MiLi */
        f << std::endl;
    }
}

/*load a file into a vector*/
static void load_file_with_separator_v(const char* name, char sep)
{
    std::ifstream f(name);
    std::vector<float> v;
    _Separator< std::vector<float> > s = Separator(v, sep);

    while (f >> s)  /* PROVIDED BY MiLi */
    {
        for (int j = 0; j < s.v.size(); ++j)
        {
            ASSERT_EQ(s.v[j], j);
        }

        ASSERT_EQ(s.v.size(), 11);
        s.v.clear();
    }
}

/* This loads a file into a list */
static void load_file_with_separator_l(const char* name, char sep)
{
    std::ifstream f(name);
    std::list<float> v;
    std::list<float>::iterator pos;
    int j;
    _Separator< std::list<float> > s = Separator(v, sep);

    while (f >> s)  /* PROVIDED BY MiLi */
    {
        j = 0;
        pos = s.v.begin();
        for (; pos != s.v.end(); pos++)
        {
            ASSERT_EQ(*pos, j);
            ++j;
        }

        ASSERT_EQ(s.v.size(), 11);
        s.v.clear();
    }
}

/* This loads a file into a set */
static void load_file_with_separator_s(const char* name, char sep)
{
    std::ifstream f(name);
    std::set<float> v;
    std::set<float>::iterator pos;
    int j;
    _Separator< std::set<float> > s = Separator(v, sep);

    while (f >> s)  /* PROVIDED BY MiLi */
    {
        j = 0;
        pos = s.v.begin();
        for (; pos != s.v.end(); pos++)
        {
            ASSERT_EQ(*pos, j);
            ++j;
        }

        ASSERT_EQ(s.v.size(), 11);
        s.v.clear();
    }
}

/* This loads a file generating an eror but not exceptions */
static void load_file_without_exception(const char* name)
{
    std::ifstream f(name);
    std::vector<float> v;

    if (!(f >> v))
    {
        ASSERT_TRUE(f.fail()); /* fail is true if either badbit or failbit is set*/
        ASSERT_FALSE(f.good());
    }

}
/* This tries to write a file then raises an exception */
static void write_file_with_exception(const char* name)
{
    std::ofstream f(name);
    std::vector<float> v;
    std::string message;
    f.exceptions(std::ifstream::badbit | std::ifstream::failbit);

    for (int j = 0; j <= 10; j++)
        insert_into(v, static_cast<float>(j));
    f.close(); /*closing file will produce an expcetion*/

    try
    {
        f << v; /* PROVIDED BY MiLi */
    }
    catch (std::exception& e)
    {
        message = e.what();
    }

    ASSERT_NE(message, ""); /* Empty message means no exception */
}

/* This tries to read a file then raises an exception */
static void read_file_with_exception(const char* name)
{

    std::ifstream f(name);
    std::vector<float> v;
    std::string message;
    f.exceptions(std::ifstream::badbit | std::ifstream::failbit);
    f.close(); /* Closing file will produce an expcetion */

    try
    {
        f >> v;  /* PROVIDED BY MiLi */
    }
    catch (std::exception& e)
    {
        message = e.what();
    }

    ASSERT_NE(message, ""); /* Empty message means no exception */
}

TEST(StreamUtilsTest, testReadWithException)
{
    const char file[] = "stream-utils.test";
    generate_file(file);
    read_file_with_exception(file);
    remove(file);
}
TEST(StreamUtilsTest, testWriteWithException)
{
    const char file[] = "stream-utils.test";
    write_file_with_exception(file);
    remove(file);
}

TEST(StreamUtilsTest, testErrosWithoutException)
{
    const char file[] = "stream-utils.test";
    load_file_without_exception(file);
    remove(file);
}


TEST(StreamUtilsTest, testReadWithGenericSeparator)
{
    const char file[] = "stream-utils.test";
    generate_file_with_separator(file, ';');
    load_file_with_separator_v(file, ';');
    load_file_with_separator_l(file, ';');
    load_file_with_separator_s(file, ';');
    remove(file);
}

