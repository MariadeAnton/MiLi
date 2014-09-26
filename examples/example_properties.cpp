/*
properties: A minimal library that implements object properties.
    This file is part of the MiLi Minimalistic Library.

    Copyright (C) Daniel Gutson, FuDePAN 2009
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

class TemperatureSensor
{
private:
    float get_celcius() const
    {
        return _celcius;
    };

    void set_celcius(float val)
    {
        _celcius = val;
    }

    float get_farenheit() const
    {
        return _celcius * (9.0f / 5.0f) + 32.0f;
    }

    void set_farenheit(float f)
    {
        _celcius = (f - 32.0f) * (5.0f / 9.0f);
    }

    float get_kelvin() const
    {
        return _celcius + 273.15f;
    }

    void set_kelvin(float k)
    {
        _celcius = k - 273.15f;
    }

public:
    PROPERTIES
    {
        PropertyRW<TemperatureSensor, float, &TemperatureSensor::get_celcius,   &TemperatureSensor::set_celcius>   celcius;
        PropertyRW<TemperatureSensor, float, &TemperatureSensor::get_farenheit, &TemperatureSensor::set_farenheit> farenheit;
        PropertyRW<TemperatureSensor, float, &TemperatureSensor::get_kelvin,    &TemperatureSensor::set_kelvin>    kelvin;
    };
private:
    float _celcius;
};

int main()
{
    TemperatureSensor s;
    s.kelvin = 0;
    float f = s.celcius;

    std::cout << f << std::endl;
    std::cout << sizeof(s) << std::endl;

    return 0;
}
