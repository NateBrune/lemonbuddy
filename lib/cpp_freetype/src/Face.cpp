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
 *  \file   src/Face.cpp
 *
 *  \date   Aug 1, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include <cpp_freetype/Face.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace freetype
{

/// overload for RefPtr<Face>::reference
template <>
void RefPtr<Face>::reference()
{
    if(m_ptr)
        FT_Reference_Face( m_ptr );
}

/// overload for RefPtr<Face>::dereference
template <>
void RefPtr<Face>::dereference()
{
    if(m_ptr)
        FT_Done_Face( m_ptr );
}

/// -------------------------------------------------------------------
///                    Structure Accessors
/// -------------------------------------------------------------------



Long& FaceDelegate::num_faces()
{
    return m_ptr->num_faces;
}

const Long& FaceDelegate::num_faces() const
{
    return m_ptr->num_faces;
}

Long& FaceDelegate::face_index()
{
    return m_ptr->face_index;
}

const Long& FaceDelegate::face_index() const
{
    return m_ptr->face_index;
}

Long& FaceDelegate::face_flags()
{
    return m_ptr->face_flags;
}

const Long& FaceDelegate::face_flags() const
{
    return m_ptr->face_flags;
}

Long& FaceDelegate::style_flags()
{
    return m_ptr->style_flags;
}

const Long& FaceDelegate::style_flags() const
{
    return m_ptr->style_flags;
}

Long& FaceDelegate::num_glyphs()
{
    return m_ptr->num_glyphs;
}

const Long& FaceDelegate::num_glyphs() const
{
    return m_ptr->num_glyphs;
}

String* FaceDelegate::family_name()
{
    return m_ptr->family_name;
}

const String* FaceDelegate::family_name() const
{
    return m_ptr->family_name;
}

String* FaceDelegate::style_name()
{
    return m_ptr->style_name;
}

const String* FaceDelegate::style_name() const
{
    return m_ptr->style_name;
}

Int& FaceDelegate::num_fixed_sizes()
{
    return m_ptr->num_fixed_sizes;
}

const Int& FaceDelegate::num_fixed_sizes() const
{
    return m_ptr->num_fixed_sizes;
}

Int& FaceDelegate::num_charmaps()
{
    return m_ptr->num_charmaps;
}

const Int& FaceDelegate::num_charmaps() const
{
    return m_ptr->num_charmaps;
}

UShort& FaceDelegate::units_per_EM()
{
    return m_ptr->units_per_EM;
}

const UShort& FaceDelegate::units_per_EM() const
{
    return m_ptr->units_per_EM;
}

Short& FaceDelegate::ascender()
{
    return m_ptr->ascender;
}

const Short& FaceDelegate::ascender() const
{
    return m_ptr->ascender;
}

Short& FaceDelegate::descender()
{
    return m_ptr->descender;
}

const Short& FaceDelegate::descender() const
{
    return m_ptr->descender;
}

Short& FaceDelegate::height()
{
    return m_ptr->height;
}

const Short& FaceDelegate::height() const
{
    return m_ptr->height;
}

Short& FaceDelegate::max_advance_width()
{
    return m_ptr->max_advance_width;
}

const Short& FaceDelegate::max_advance_width() const
{
    return m_ptr->max_advance_width;
}

Short& FaceDelegate::max_advance_height()
{
    return m_ptr->max_advance_height;
}

const Short& FaceDelegate::max_advance_height() const
{
    return m_ptr->max_advance_height;
}

Short& FaceDelegate::underline_position()
{
    return m_ptr->underline_position;
}

const Short& FaceDelegate::underline_position() const
{
    return m_ptr->underline_position;
}

Short& FaceDelegate::underline_thickness()
{
    return m_ptr->underline_thickness;
}

const Short& FaceDelegate::underline_thickness() const
{
    return m_ptr->underline_thickness;
}

RefPtr<GlyphSlot> FaceDelegate::glyph()
{
    return RefPtr<GlyphSlot>(m_ptr->glyph,true);
}

bool FaceDelegate::has_horizontal()
{
    return FT_HAS_HORIZONTAL( m_ptr );
}

bool FaceDelegate::has_vertical()
{
    return FT_HAS_VERTICAL( m_ptr );
}

bool FaceDelegate::has_kerning()
{
    return FT_HAS_KERNING( m_ptr );
}

bool FaceDelegate::is_scalable()
{
    return FT_IS_SCALABLE( m_ptr );
}

bool FaceDelegate::is_sfnt()
{
    return FT_IS_SFNT( m_ptr );
}

bool FaceDelegate::is_fixed_width()
{
    return FT_IS_FIXED_WIDTH( m_ptr );
}

bool FaceDelegate::has_fixed_sizes()
{
    return FT_HAS_FIXED_SIZES( m_ptr );
}

bool FaceDelegate::has_fast_glyphs()
{
    return FT_HAS_FAST_GLYPHS( m_ptr );
}

bool FaceDelegate::has_glyph_names()
{
    return FT_HAS_GLYPH_NAMES( m_ptr );
}

bool FaceDelegate::has_multiple_masters()
{
    return FT_HAS_MULTIPLE_MASTERS( m_ptr );
}

bool FaceDelegate::is_cid_keyed()
{
    return FT_IS_CID_KEYED( m_ptr );
}

bool FaceDelegate::is_tricky()
{
    return FT_IS_TRICKY( m_ptr );
}

/// -------------------------------------------------------------------
///                       Member Functions
/// -------------------------------------------------------------------

Error FaceDelegate::select_size(Int strike_index)
{
    return FT_Select_Size(m_ptr, strike_index);
}

Error FaceDelegate::set_char_size(F26Dot6 char_width, F26Dot6 char_height,
        UInt horz_resolution, UInt vert_resolution)
{
    return FT_Set_Char_Size(m_ptr, char_width, char_height,
            horz_resolution, vert_resolution);
}


Error FaceDelegate::set_pixel_sizes(UInt pixel_width, UInt pixel_height)
{
    return FT_Set_Pixel_Sizes(m_ptr, pixel_width, pixel_height);
}

Error FaceDelegate::load_glyph(UInt glyph_index, Int32 load_flags)
{
    return FT_Load_Glyph( m_ptr, glyph_index, load_flags );
}

Error FaceDelegate::load_char(ULong char_code, Int32 load_flags)
{
    return FT_Load_Char( m_ptr, char_code, load_flags );
}

Error FaceDelegate::get_glyph_name(
                        UInt      glyph_index,
                        Pointer   buffer,
                        UInt      buffer_max )
{
    return FT_Get_Glyph_Name( m_ptr, glyph_index, buffer, buffer_max );
}

const char* FaceDelegate::get_postscript_name()
{
    return FT_Get_Postscript_Name( m_ptr );
}

Error FaceDelegate::select_charmap( Encoding encoding )
{
    return FT_Select_Charmap( m_ptr, (FT_Encoding)encoding );
}

Error FaceDelegate::set_charmap( UInt id )
{
    return FT_Set_Charmap(m_ptr, m_ptr->charmaps[id] );
}

UInt FaceDelegate::get_char_index( ULong charcode )
{
    return FT_Get_Char_Index( m_ptr, charcode );
}

ULong FaceDelegate::get_first_char( UInt& agindex )
{
    return FT_Get_First_Char( m_ptr, &agindex );
}

ULong FaceDelegate::get_next_char( ULong char_code, UInt& agindex )
{
    return FT_Get_Next_Char( m_ptr, char_code, &agindex );
}

UInt FaceDelegate::get_name_index( String* glyph_name )
{
    return FT_Get_Name_Index( m_ptr, glyph_name) ;
}

UShort FaceDelegate::get_fstype_flags()
{
    return FT_Get_FSType_Flags( m_ptr );
}

} // namespace freetype 
