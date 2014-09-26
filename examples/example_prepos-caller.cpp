/*
prepos_caller: A minimal library for wrapping object methods calls.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Gutson, FuDePAN 2008-2009
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
#include "mili/mili.h"
#include "mili/prepos_printer.h"
#include "mili/prepos_mutex.h"

using namespace mili;
using namespace std;

class Test
{
public:
    void f()
    {
        cout << "f" << endl;
    }
};


///

void sample_using_print()
{
    cout << "Sample using print:\n";
    Test t;
    PrePosPrinter pre("pre"), pos("pos");
    PrePosCaller<Test* const, PrePosPrinter, PrePosPrinter> ppc(&t, pre, pos);

    ppc->f();
}


void sample_using_mutex()
{
    cout << "\nSample using a mutex:\n";
    Test t;
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    PreMutex pre(&mutex);
    PosMutex pos(&mutex);

    PrePosCaller<Test* const, PreMutex, PosMutex> ppc(&t, pre, pos);

    ppc->f();
}


void sample_using_mutex_and_print()
{
    cout << "\nSample using both a mutex and printing:\n";
    Test t;

    PrePosPrinter pre_print("pre"), pos_print("pos");

    typedef PrePosCaller<Test* const, PrePosPrinter, PrePosPrinter> PPC_Printer;

    PPC_Printer ppc_printer(&t, pre_print, pos_print);


    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    PreMutex preMutex(&mutex);
    PosMutex posMutex(&mutex);

    PrePosCaller<PPC_Printer, PreMutex, PosMutex> ppc(ppc_printer, preMutex, posMutex);

    ppc->f();
}

int main()
{
    sample_using_print();

    sample_using_mutex();

    sample_using_mutex_and_print();

    return 0;
}
