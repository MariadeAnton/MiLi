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

#include "google/gtest/gtest.h"
#include "google/gmock/gmock.h"
#include "mili/mili.h"

using namespace mili;

class Mock
{
public:
    MOCK_METHOD1(mocked_set_celcius, void(float));
    MOCK_CONST_METHOD0(mocked_get_celcius, void());
};

class TemperatureSensor
{
private:
    float get_celcius() const
    {
        mock.mocked_get_celcius();
        return _celcius;
    };

    void set_celcius(float val)
    {
        _celcius = val;
        mock.mocked_set_celcius(val);
    }

public:
    PROPERTIES
    {
        PropertyRW<TemperatureSensor, float, &TemperatureSensor::get_celcius, &TemperatureSensor::set_celcius>   celcius;
    };
    Mock mock;
private:
    float _celcius;
};

TEST(Properties, test)
{
    TemperatureSensor s;
    EXPECT_CALL(s.mock, mocked_set_celcius(0));
    s.celcius = 0;
    EXPECT_CALL(s.mock, mocked_get_celcius());
    float f = s.celcius;
    ASSERT_EQ(f, 0);
}
