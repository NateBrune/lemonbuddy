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
 *  along with Fontconfigmm.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 *  \file   src/cppfreetype.cpp
 *
 *  \date   Aug 1, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include <ft2build.h>
#include FT_FREETYPE_H

#include <cpp_freetype/cpp_freetype.h>
#include <iostream>

namespace freetype
{
    const unsigned int MAJOR = FREETYPE_MAJOR;
    const unsigned int MINOR = FREETYPE_MINOR;
    const unsigned int PATCH = FREETYPE_PATCH;

    /// initialize freetype
    RefPtr<Library> init()
    {
        FT_Library ptr;
        FT_Init_FreeType(&ptr);

        // give an extra reference count which we'llt ake away in the
        // done functoin
        return RefPtr<Library>(ptr,true);
    }

    /// initialize freetype, returns error code as well
    RValuePair< RefPtr<Library>, Error > init_e()
    {
        FT_Library ptr;
        Error      err = FT_Init_FreeType(&ptr);

        RValuePair< RefPtr<Library>, Error > pair
            ( RefPtr<Library>(ptr), err );

        // give an extra reference count which we'llt ake away in the
        // done functoin
        return pair;
    }

    Error done(RefPtr<Library>& library)
    {
        FT_Library ptr = library.subvert();

        // doing this will decrease the reference count, so that's
        // why we added an extra refrence in init(). This is necessary
        // so that when the calling library object goes out of scope it
        // doesn't try to actually destroy anything
        library.unlink();

        return FT_Done_FreeType( ptr );
    }

}







