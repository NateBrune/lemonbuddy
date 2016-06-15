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
 *  @file   src/GlyphSlot.cpp
 *
 *  @date   Feb 5, 2013
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  
 */


#include <cpp_freetype/GlyphSlot.h>
#include <cpp_freetype/Library.h>
#include <cpp_freetype/Face.h>

namespace freetype {

/// specialization for RefPtr<GlyphSlot>::reference
/**
 *  @note   since a glyph slot is unique to a face a glyph slot reference
 *          references the face
 */
template <>
void RefPtr<GlyphSlot>::reference()
{
    FT_Reference_Face( m_ptr->face );
}

/// specialization for RefPtr<GlyphSlot>::dereference
/**
 *  @note   since a glyph slot is unique to a face a glyph slot reference
 *          dereferences the face
 */
template <>
void RefPtr<GlyphSlot>::dereference()
{
    FT_Done_Face( m_ptr->face );
}

RefPtr<Library> GlyphSlotDelegate::library()
{
    return RefPtr<Library>( m_ptr->library, true );
}

RefPtr<Face> GlyphSlotDelegate::face()
{
    return RefPtr<Face>( m_ptr->face, true );
}

RefPtr<GlyphSlot> GlyphSlotDelegate::next()
{
    return RefPtr<GlyphSlot>( m_ptr->next, true );
}

RefPtr<Outline> GlyphSlotDelegate::outline()
{
    return RefPtr<Outline>( &(m_ptr->outline) );
}

void GlyphSlotDelegate::linearHoriAdvance( Fixed val )
{
    m_ptr->linearHoriAdvance = val;
}


Fixed GlyphSlotDelegate::linearHoriAdvance( ) const
{
    return m_ptr->linearHoriAdvance;
}



void GlyphSlotDelegate::linearVertAdvance( Fixed val )
{
    m_ptr->linearVertAdvance = val;
}


Fixed GlyphSlotDelegate::linearVertAdvance( ) const
{
    return m_ptr->linearVertAdvance;
}



void GlyphSlotDelegate::format( GlyphFormat val )
{
    m_ptr->format = (FT_Glyph_Format)val;
}


GlyphFormat GlyphSlotDelegate::format( ) const
{
    return (GlyphFormat)m_ptr->format;
}



void GlyphSlotDelegate::lsb_delta( Pos val )
{
    m_ptr->lsb_delta = val;
}


Pos GlyphSlotDelegate::lsb_delta( ) const
{
    return m_ptr->lsb_delta;
}



void GlyphSlotDelegate::rsb_delta( Pos val )
{
    m_ptr->rsb_delta = val;
}


Pos GlyphSlotDelegate::rsb_delta( ) const
{
    return m_ptr->rsb_delta;
}





}







