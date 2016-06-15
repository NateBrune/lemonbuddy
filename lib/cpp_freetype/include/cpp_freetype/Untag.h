/*
 *  Copyright (C) 2012 Josh Bialkowski (jbialk@mit.edu)
 *
 *  This file is part of cppfreetype.
 *
 *  cppfreetype is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  cppfreetype is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with cppfreetype.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 *  @file   include/cppfreetype/Untag.h
 *
 *  @date   Feb 5, 2013
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  
 */

#ifndef CPPFREETYPE_UNTAG_H_
#define CPPFREETYPE_UNTAG_H_

#include <ft2build.h>
#include FT_FREETYPE_H

#include <cpp_freetype/types.h>
#include <ostream>

namespace freetype {

class Untag
{
    private:
        UInt32_t    m_tag;

    public:
        Untag( UInt32_t tag=0 );
        Untag& operator=( const UInt32_t& val );
        char operator[](int i) const;
};

}

std::ostream& operator<<( std::ostream& out, const freetype::Untag& u );














#endif // UNTAG_H_
