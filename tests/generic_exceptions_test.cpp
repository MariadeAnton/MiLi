/*
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Hugo Arregui, FuDePAN 2012
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

class LocationExceptionHierarchy {};

typedef mili::GenericException<LocationExceptionHierarchy> LocationException;

DEFINE_SPECIFIC_EXCEPTION_TEXT(InvalidLocation, LocationExceptionHierarchy, "The location is not defined");

TEST(GenericException, test)
{
    InvalidLocation l;
    ASSERT_EQ(std::string("The location is not defined"), std::string(l.what()));
}

