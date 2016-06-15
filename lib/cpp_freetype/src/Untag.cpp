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
 *  along with gltk.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 *  @file   src/Untag.cpp
 *
 *  @date   Feb 5, 2013
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  
 */

#include <cpp_freetype/Untag.h>

namespace freetype {

Untag::Untag( UInt32_t tag ):
    m_tag(tag)
{}

Untag& Untag::operator=( const UInt32_t& val )
{
    m_tag = val;
    return *this;
}

char Untag::operator[](int i) const
{
    if( i < 0 || i > 3 )
        return 0;

    return (m_tag >> (24 - 8*i)) & 0xFF;
}

}

std::ostream& operator<<( std::ostream& out, const freetype::Untag& u )
{
    for(int i=0; i < 4; i++)
        out << u[i];
    return out;
}


