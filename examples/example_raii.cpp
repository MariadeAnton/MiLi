/*
raii: A minimal library for generic RAII implementation
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Lucas Besso & Raul Striglio, FuDePAN 2011
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
#include <cstdio>
#include "mili/mili.h"

using namespace mili;

class file
{

public:
    file(std::string path): _file(std::fopen(path.c_str(), "w")) {}
    void close()
    {
        fclose(_file);
    }
    void write(std::string str)
    {
        std::fputs(str.c_str(), _file);
    }

private:
    std::FILE* _file;
};

int main()
{
    file fi("file");
    RAII<file, &file::close> rs(fi);
    fi.write("new line in the file");

    return 0;
}
