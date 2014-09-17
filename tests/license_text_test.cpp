/*
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Leandro Ramos, FuDePAN 2012
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

using namespace mili;
using namespace std;

TEST(BoostDisclaimer, correctOutputTest)
{
    const string correctDisclaimer = "ViSi 1.0\n"
                                     "Copyright (C) Leandro Ramos, Pablo Oliva, FuDePAN 2012\n"
                                     "This program comes with ABSOLUTELY NO WARRANTY; for details see http://www.boost.org/LICENSE_1_0.txt\n"
                                     "ViSi is free software, and you are welcome to redistribute it under certain conditions; for more information visit http://www.boost.org/LICENSE_1_0.txt\n\n";
    const string returnDisclaimer = getBoostLicenseText("ViSi", "1.0", "Leandro Ramos, Pablo Oliva", "2012");                                  
    ASSERT_EQ(correctDisclaimer, returnDisclaimer);
}
