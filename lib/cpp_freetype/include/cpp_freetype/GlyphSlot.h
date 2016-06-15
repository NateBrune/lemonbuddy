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
 *  @file   include/cppfreetype/GlyphSlot.h
 *
 *  @date   Feb 5, 2013
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  
 */

#ifndef CPPFREETYPE_GLYPHSLOT_H_
#define CPPFREETYPE_GLYPHSLOT_H_

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MODULE_H

#include <cpp_freetype/types.h>
#include <cpp_freetype/RefPtr.h>
#include <cpp_freetype/Outline.h>

namespace freetype {

class GlyphSlot;
class Library;
class Face;

class GlyphSlotDelegate
{
    private:
        FT_GlyphSlot m_ptr;

        /// constructable only by RefPtr<Face>
        GlyphSlotDelegate( FT_GlyphSlot ptr=0 ):
            m_ptr(ptr)
        {}

        /// not copy-constructable
        GlyphSlotDelegate( const GlyphSlotDelegate& );

        /// not copy-assignable
        GlyphSlotDelegate& operator=( const GlyphSlotDelegate& );

    public:
        friend class RefPtr<GlyphSlot>;

        GlyphSlotDelegate* operator->(){ return this; }
        const GlyphSlotDelegate* operator->() const{ return this; }

        RefPtr<Library>     library();
        RefPtr<Face>        face();
        RefPtr<GlyphSlot>   next();

        RefPtr<Outline>     outline();

        void linearHoriAdvance( Fixed );
        Fixed linearHoriAdvance() const;

        void linearVertAdvance( Fixed );
        Fixed linearVertAdvance() const;

        void format(GlyphFormat);
        GlyphFormat format() const;

        void lsb_delta( Pos );
        Pos lsb_delta() const;

        void rsb_delta( Pos );
        Pos rsb_delta() const;

};


/// traits class for a GlyphSlot, a face's storage location for storing a
/// glyph image
struct GlyphSlot
{
    typedef GlyphSlotDelegate   Delegate;
    typedef FT_GlyphSlot        Storage;
    typedef FT_GlyphSlot        cobjptr;
};



}
















#endif // GLYPHSLOT_H_
