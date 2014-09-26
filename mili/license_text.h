/*
license_text: A library that implements functions to show software licenses.
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
*/

#ifndef LICENSE_TEXT_H
#define LICENSE_TEXT_H
#include <string>
NAMESPACE_BEGIN

inline std::string getBoostLicenseText( const std::string& project_name, 
                                        const std::string& version, 
                                        const std::string& copyright_names, 
                                        const std::string& years_from_to)
{
    return project_name + " " + version + "\n"
           + "Copyright (C) " + copyright_names + ", FuDePAN " + years_from_to + "\n"
           + "This program comes with ABSOLUTELY NO WARRANTY; for details see http://www.boost.org/LICENSE_1_0.txt\n"
           +  project_name + " is free software, and you are welcome to redistribute it under certain conditions; for more information visit http://www.boost.org/LICENSE_1_0.txt\n\n";
}

NAMESPACE_END

#endif

