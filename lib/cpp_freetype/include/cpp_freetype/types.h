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
 *  \file   include/cppfreetype/types.h
 *
 *  \date   Aug 1, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef CPPFREETYPE_TYPES_H_
#define CPPFREETYPE_TYPES_H_

#include <ft2build.h>
#include FT_FREETYPE_H

#include <cstring>
#include <cstddef>
#include <sigc++/sigc++.h>

/// root namespace for freetype
namespace freetype
{


extern const unsigned int MAJOR;
extern const unsigned int MINOR;
extern const unsigned int PATCH;

typedef FT_Byte         Byte_t;     ///< simple typedef unsigned char
typedef FT_Bytes        Bytes_t;    ///< a typedef for constant memory area
typedef FT_Char         Char_t;     ///< simple typedef for signed char
typedef FT_Int          Int_t;      ///< typedef for int
typedef FT_UInt         UInt_t;     ///< typedef for unsigned int
typedef FT_Int16        Int16_t;    ///< typedef for 16bit integer
typedef FT_UInt16       UInt16_t;   ///< typedef for 16bit unsigned int
typedef FT_Int32        Int32_t;    ///< typedef for 32bit signed int
typedef FT_UInt32       UInt32_t;   ///< typedef for 32bit unsigned int
typedef FT_Short        Short_t;    ///< simlpe typedef for signed short
typedef FT_UShort       UShort_t;   ///< simple typedef for unsigned short
typedef FT_Long         Long_t;     ///< simple typedef for signed long
typedef FT_ULong        ULong_t;    ///< simple typedef for unsigned long
typedef FT_Bool         Bool_t;     ///< used for simple booleans,
                                    /// 1=true, 0=false
typedef FT_Offset       Offset_t;   ///< the largest unsigned integer type
                                    ///  used to express a file size or
                                    ///  position or a memory block size
typedef FT_PtrDist      PtrDist_t;  ///< the largest signed integer type
                                    ///  used to express a distance between
                                    ///  two pointers
typedef FT_String       String_t;   ///< simple typedef for char
typedef FT_Tag          Tag_t;      ///< typedef for 32bit tags (as used in
                                    ///  the SFNT format)
typedef FT_Error        Error_t;    ///< FreeType error code, a value of
                                    ///  0 is always interpreted as a
                                    ///  successful operation
typedef FT_Fixed        Fixed_t;    ///< Used to store 16.16 fixed float
                                    ///  values, like scaling values or
                                    ///  matrix coefficients
typedef FT_Pointer      Pointer_t;  ///< simple typedef for typeless ptr
typedef FT_Pos          Pos_t;      ///< used to store vectoral coordinates.
                                    ///  depending on the context these
                                    ///  represent distances in integer
                                    ///  font units, or 16.16, or
                                    ///  26.6 fixed float pixel coords
typedef FT_FWord        FWord_t;    ///< signed 16bit integer used to
                                    ///  store distance in original font
                                    ///  units
typedef FT_UFWord       UFWord_t;   ///< unsigned 16bit integer used to
                                    ///  store distance in original font
                                    ///  units
typedef FT_F2Dot14      F2Dot14_t;  ///< signed 2.14 fixed float type used
                                    ///  for unit vectors
typedef FT_F26Dot6      F26Dot6_t;  ///< signed 26.6 fixed float type used
                                    ///  for vectoral pixel coordinates

typedef FT_Byte         Byte;       ///< simple typedef unsigned char
typedef FT_Bytes        Bytes;      ///< a typedef for constant memory area
typedef FT_Char         Char;       ///< simple typedef for signed char
typedef FT_Int          Int;        ///< typedef for int
typedef FT_UInt         UInt;       ///< typedef for unsigned int
typedef FT_Int16        Int16;      ///< typedef for 16bit integer
typedef FT_UInt16       UInt16;     ///< typedef for 16bit unsigned int
typedef FT_Int32        Int32;      ///< typedef for 32bit signed int
typedef FT_UInt32       UInt32;     ///< typedef for 32bit unsigned int
typedef FT_Short        Short;      ///< simlpe typedef for signed short
typedef FT_UShort       UShort;     ///< simple typedef for unsigned short
typedef FT_Long         Long;       ///< simple typedef for signed long
typedef FT_ULong        ULong;      ///< simple typedef for unsigned long
typedef FT_Bool         Bool;       ///< used for simple booleans,
                                    /// 1=true, 0=false
typedef FT_Offset       Offset;     ///< the largest unsigned integer type
                                    ///  used to express a file size or
                                    ///  position or a memory block size
typedef FT_PtrDist      PtrDist;    ///< the largest signed integer type
                                    ///  used to express a distance between
                                    ///  two pointers
typedef FT_String       String;     ///< simple typedef for char
typedef FT_Tag          Tag;        ///< typedef for 32bit tags (as used in
                                    ///  the SFNT format)
typedef FT_Error        Error;      ///< FreeType error code, a value of
                                    ///  0 is always interpreted as a
                                    ///  successful operation
typedef FT_Fixed        Fixed;      ///< Used to store 16.16 fixed float
                                    ///  values, like scaling values or
                                    ///  matrix coefficients
typedef FT_Pointer      Pointer;    ///< simple typedef for typeless ptr
typedef FT_Pos          Pos;        ///< used to store vectoral coordinates.
                                    ///  depending on the context these
                                    ///  represent distances in integer
                                    ///  font units, or 16.16, or
                                    ///  26.6 fixed float pixel coords
typedef FT_FWord        FWord;      ///< signed 16bit integer used to
                                    ///  store distance in original font
                                    ///  units
typedef FT_UFWord       UFWord;     ///< unsigned 16bit integer used to
                                    ///  store distance in original font
                                    ///  units
typedef FT_F2Dot14      F2Dot14;    ///< signed 2.14 fixed float type used
                                    ///  for unit vectors
typedef FT_F26Dot6      F26Dot6;    ///< signed 26.6 fixed float type used
                                    ///  for vectoral pixel coordinates


/// namespace wrapper for PixelMode enumeration
/**
 *  @see PixelMode
 */
namespace pixelmode
{
    /// An enumeration type used to describe the format of pixels in a
    /// given bitmap.

    /**
     *  @note: additional formats may be added in the future.
     */
    enum PixelMode
    {
        NONE    = 0,    ///< reserved
        MONO,   ///<  A monochrome bitmap, using 1 bit per pixel. Note that
                ///   pixels are stored in most-significant order (MSB),
                ///   which means that the left-most pixel in a byte has
                ///   value 128.
        GRAY,   ///<  An 8-bit bitmap, generally used to represent
                ///   anti-aliased glyph images. Each pixel is stored in
                ///   one byte. Note that the number of ‘gray’ levels is
                ///   stored in the ‘num_grays’ field of the FT_Bitmap
                ///   structure (it generally is 256).
        GRAY2,  ///<  A 2-bit per pixel bitmap, used to represent embedded
                ///   anti-aliased bitmaps in font files according to the
                ///   OpenType specification. We haven't found a single
                ///   font using this format, however.
        GRAY4,  ///<  A 4-bit per pixel bitmap, representing embedded
                ///   anti-aliased bitmaps in font files according to the
                ///   OpenType specification. We haven't found a single
                ///   font using this format, however.
        LCD,    ///<  An 8-bit bitmap, representing RGB or BGR decimated
                ///   glyph images used for display on LCD displays; the
                ///   bitmap is three times wider than the original glyph
                ///   image. See also FT_RENDER_MODE_LCD.
        LCD_V,  ///<  An 8-bit bitmap, representing RGB or BGR decimated
                ///   glyph images used for display on rotated LCD
                ///   displays; the bitmap is three times taller than the
                ///   original glyph image. See also FT_RENDER_MODE_LCD_V.
        MAX     ///<  used for iterating over enum
    };

}

/// template used to replace the FT_IMAGE_TAG macro: converts four-letter
/// tags into an unsigned long type
/**
 * @note Since many 16-bit compilers don't like 32-bit enumerations, you
 *       should redefine this macro in case of problems to something like
 *       this:
 *       @code
#define FT_IMAGE_TAG( value, _x1, _x2, _x3, _x4 )  value
@endcode
 *       to get a simple enumeration without assigning special numbers.
 */
template < ULong_t x1, ULong_t x2, ULong_t x3, ULong_t x4 >
struct ImageTag
{
    static const ULong_t value =
              ( (ULong_t) x1 << 24 )
            | ( (ULong_t) x2 << 16 )
            | ( (ULong_t) x3 <<  8 )
            | ( (ULong_t) x4 <<  0 );
};

/// namespace wrapper for GlyphFormat enumeration
/**
 *  @see GlyphFormat
 */
namespace glyphformat
{
    /// An enumeration type used to describe the format of a given glyph
    /// image.
    /**
     *  @note   Note that this version of FreeType only supports two image
     *          formats, even though future font drivers will be able to
     *          register their own format.
     */
    enum GlyphFormat
    {
        /// The value 0 is reserved.
        NONE        = ImageTag<0,0,0,0>::value,

        /// The glyph image is a composite of several other images. This
        /// format is only used with FT_LOAD_NO_RECURSE, and is used to
        /// report compound glyphs (like accented characters).
        COMPOSITE   = ImageTag<'c','o','m','p'>::value,

        /// The glyph image is a bitmap, and can be described as an
        /// FT_Bitmap. You generally need to access the ‘bitmap’ field of
        /// the FT_GlyphSlotRec structure to read it.
        BITMAP      = ImageTag<'b','i','t','s'>::value,

        /// The glyph image is a vectorial outline made of line segments
        ///  and Bézier arcs; it can be described as an FT_Outline; you
        /// generally want to access the ‘outline’ field of the
        /// FT_GlyphSlotRec structure to read it.
        OUTLINE     = ImageTag<'o','u','t','l'>::value,

        /// The glyph image is a vectorial path with no inside and outside
        /// contours. Some Type 1 fonts, like those in the Hershey family,
        /// contain glyphs in this format. These are described as
        /// FT_Outline, but FreeType isn't currently capable of rendering
        /// them correctly.
        PLOTTER     = ImageTag<'p','l','o','t'>::value
    };
}

typedef glyphformat::GlyphFormat GlyphFormat;

/// Describe a function used to destroy the ‘client’ data of any FreeType
/// object. See the description of the FT_Generic type for details of usage.
/**
 *  input: The address of the FreeType object which is under finalization.
 *         Its client data is accessed through its ‘generic’ field.
 */
typedef sigc::slot<void,void*>  GenericFinalizer_t;


/// a function used to allocate bytes from memory
/**
 *  Input parameter will be number of bytes requested and the function should
 *  return a pointer to a memory block or 0 in case of failure
 */
typedef sigc::slot<void*,long>  AllocFunc_t;

/// a function used to release a given block of memory
/**
 *  Input parameter is a pointer to a block of memory returned from
 *  the associated allocator
 */
typedef sigc::slot<void,void*>  FreeFunc_t;

/// a function used to re-allocate a given block of memory
/**
 *  Parameters are:
 *  # \p cur_size   the block's current size in bytes
 *  # \p new_size   the block's requested size
 *  # \p block      the block's current address
 *
 *  Return value is the new block address, or 0 in the case of memory
 *  shortage
 *
 *  @note   In case of error the old block must still be available
 */
typedef sigc::slot<void*,long,long,void*>  ReallocFunc_t;



/// A list of bit flags used in the ‘face_flags’ field of the FT_FaceRec
/// structure. They inform client applications of properties of the
/// corresponding face.
namespace faceflag
{
    /// Indicates that the face contains outline glyphs. This doesn't prevent
    /// bitmap strikes, i.e., a face can have both this and and
    /// FT_FACE_FLAG_FIXED_SIZES set.
    const ULong_t   SCALABLE            = ( 1L <<  0 );

    /// Indicates that the face contains bitmap strikes. See also the
    /// ‘num_fixed_sizes’ and ‘available_sizes’ fields of FT_FaceRec.
    const ULong_t   FIXED_SIZES         = ( 1L <<  1 );

    /// Indicates that the face contains fixed-width characters (like Courier,
    /// Lucido, MonoType, etc.).
    const ULong_t   FIXED_WIDTH         = ( 1L <<  2 );

    /// Indicates that the face uses the ‘sfnt’ storage scheme. For now, this
    /// means TrueType and OpenType.
    const ULong_t   SFNT                = ( 1L <<  3 );

    /// Indicates that the face contains horizontal glyph metrics. This should
    /// be set for all common formats.
    const ULong_t   HORIZONTAL          = ( 1L <<  4 );

    /// Indicates that the face contains vertical glyph metrics. This is only
    /// available in some formats, not all of them.
    const ULong_t   VERTICAL            = ( 1L <<  5 );

    /// Indicates that the face contains kerning information. If set, the
    /// kerning distance can be retrieved through the function FT_Get_Kerning.
    /// Otherwise the function always return the vector (0,0). Note that
    /// FreeType doesn't handle kerning data from the ‘GPOS’ table (as present
    /// in some OpenType fonts).
    const ULong_t   KERNING             = ( 1L <<  6 );

    /// THIS FLAG IS DEPRECATED. DO NOT USE OR TEST IT.
    const ULong_t   FAST_GLYPHS         = ( 1L <<  7 );

    /// Indicates that the font contains multiple masters and is capable of
    /// interpolating between them. See the multiple-masters specific API for
    /// details.
    const ULong_t   MULTIPLE_MASTERS    = ( 1L <<  8 );

    /// Indicates that the font contains glyph names that can be retrieved
    /// through FT_Get_Glyph_Name. Note that some TrueType fonts contain
    /// broken glyph name tables. Use the function FT_Has_PS_Glyph_Names when
    /// needed.
    const ULong_t   GLYPH_NAMES         = ( 1L <<  9 );

    /// Used internally by FreeType to indicate that a face's stream was
    /// provided by the client application and should not be destroyed when
    /// FT_Done_Face is called. Don't read or test this flag.
    const ULong_t   EXTERNAL_STREAM     = ( 1L << 10 );

    /// Set if the font driver has a hinting machine of its own. For example,
    /// with TrueType fonts, it makes sense to use data from the SFNT ‘gasp’
    /// table only if the native TrueType hinting engine (with the bytecode
    /// interpreter) is available and active.
    const ULong_t   HINTER              = ( 1L << 11 );

    /// Set if the font is CID-keyed. In that case, the font is not accessed
    /// by glyph indices but by CID values. For subsetted CID-keyed fonts this
    /// has the consequence that not all index values are a valid argument to
    /// FT_Load_Glyph. Only the CID values for which corresponding glyphs in
    /// the subsetted font exist make FT_Load_Glyph return successfully; in
    /// all other cases you get an ‘FT_Err_Invalid_Argument’ error.
    ///
    /// Note that CID-keyed fonts which are in an SFNT wrapper don't have
    /// this flag set since the glyphs are accessed in the normal way (using
    /// contiguous indices); the ‘CID-ness’ isn't visible to the application.
    const ULong_t   CID_KEYED           = ( 1L << 12 );

    /// Set if the font is ‘tricky’, this is, it always needs the font
    /// format's native hinting engine to get a reasonable result. A typical
    /// example is the Chinese font ‘mingli.ttf’ which uses TrueType bytecode
    /// instructions to move and scale all of its subglyphs.
    ///
    /// It is not possible to autohint such fonts using FT_LOAD_FORCE_AUTOHINT;
    /// it will also ignore FT_LOAD_NO_HINTING. You have to set both
    /// FT_LOAD_NO_HINTING and FT_LOAD_NO_AUTOHINT to really disable hinting;
    /// however, you probably never want this except for demonstration
    /// purposes.
    ///
    /// Currently, there are about a dozen TrueType fonts in the list of
    /// tricky fonts; they are hard-coded in file ‘ttobjs.c’.
    const ULong_t   TRICKY              = ( 1L << 13 );
}


/// A list of bit-flags used to indicate the style of a given face. These are
/// used in the ‘style_flags’ field of FT_FaceRec.
/**
 *  @note   The style information as provided by FreeType is very basic. More
 *          details are beyond the scope and should be done on a higher level
 *          (for example, by analyzing various fields of the ‘OS/2’ table in
 *          SFNT based fonts).
 */
namespace styleflag
{
    /// Indicates that a given face style is italic or oblique.
    const UInt_t    ITALIC  = ( 1 << 0 );

    /// Indicates that a given face is bold.
    const UInt_t    BOLD    = ( 1 << 1 );


}


/// A list of bit-field constants used with FT_Load_Glyph to indicate what
/// kind of operations to perform during glyph loading.
namespace load
{
    /// Corresponding to 0, this value is used as the default glyph load operation.
    /**
     *
     *  In this case, the following happens:
     *  #   FreeType looks for a bitmap for the glyph corresponding to the
     *      face's current size. If one is found, the function returns. The
     *      bitmap data can be accessed from the glyph slot (see note below).
     *  #   If no embedded bitmap is searched or found, FreeType looks for a
     *      scalable outline. If one is found, it is loaded from the font
     *      file, scaled to device pixels, then ‘hinted’ to the pixel grid in
     *      order to optimize it. The outline data can be accessed from the
     *      glyph slot (see note below).
     *
     *  Note that by default, the glyph loader doesn't render outlines into
     *  bitmaps. The following flags are used to modify this default behaviour
     *  to more specific and useful cases.
     *
     *  @note
     *  By default, hinting is enabled and the font's native hinter (see
     *  FT_FACE_FLAG_HINTER) is preferred over the auto-hinter. You can
     *  disable hinting by setting FT_LOAD_NO_HINTING or change the precedence
     *  by setting FT_LOAD_FORCE_AUTOHINT. You can also set
     *  FT_LOAD_NO_AUTOHINT in case you don't want the auto-hinter to be
     *  used at all.
     *
     *  See the description of FT_FACE_FLAG_TRICKY for a special exception
     *  (affecting only a handful of Asian fonts).
     *
     *  Besides deciding which hinter to use, you can also decide which
     *  hinting algorithm to use. See FT_LOAD_TARGET_XXX for details.
     *
     *  Note that the auto-hinter needs a valid Unicode cmap (either a native
     *  one or synthesized by FreeType) for producing correct results. If a
     *  font provides an incorrect mapping (for example, assigning the
     *  character code U+005A, LATIN CAPITAL LETTER Z, to a glyph depicting a
     *  mathematical integral sign), the auto-hinter might produce useless
     *  results.
     */
    const UInt_t DEFAULT                      = FT_LOAD_DEFAULT;

    /// Don't scale the outline glyph loaded, but keep it in font units.
    /**
     *  This flag implies FT_LOAD_NO_HINTING and FT_LOAD_NO_BITMAP, and unsets
     *  FT_LOAD_RENDER.
     */
    const UInt_t NO_SCALE                     = FT_LOAD_NO_SCALE;

    /// Disable hinting.
    /**
     *  This generally generates ‘blurrier’ bitmap glyph when
     *  the glyph is rendered in any of the anti-aliased modes. See also the
     *  note below.
     *
     *  This flag is implied by FT_LOAD_NO_SCALE.
     */
    const UInt_t NO_HINTING                   = FT_LOAD_NO_HINTING;

    /// Call FT_Render_Glyph after the glyph is loaded
    /*
     *  By default, the glyph is rendered in FT_RENDER_MODE_NORMAL mode. This
     *  can be overridden by FT_LOAD_TARGET_XXX or FT_LOAD_MONOCHROME.
     *
     *  This flag is unset by FT_LOAD_NO_SCALE.
     */
    const UInt_t RENDER                       = FT_LOAD_RENDER;

    /// Ignore bitmap strikes when loading. Bitmap-only fonts ignore this flag.
    /*
     *  FT_LOAD_NO_SCALE always sets this flag.
     */
    const UInt_t NO_BITMAP                    = FT_LOAD_NO_BITMAP;

    /// Load the glyph for vertical text layout.
    /*
     *  Don't use it as it is problematic currently.
     */
    const UInt_t VERTICAL_LAYOUT              = FT_LOAD_VERTICAL_LAYOUT;

    /// Indicates that the auto-hinter is preferred over the font's native
    /// hinter.
    /*
     *  See also the note below.
     */
    const UInt_t FORCE_AUTOHINT               = FT_LOAD_FORCE_AUTOHINT;

    /// Indicates that the font driver should crop the loaded bitmap glyph
    /// (i.e., remove all space around its black bits).
    /*
     *  Not all drivers implement this.
     */
    const UInt_t CROP_BITMAP                  = FT_LOAD_CROP_BITMAP;

    /// Indicates that the font driver should perform pedantic verifications
    /// during glyph loading.
    /*
     * This is mostly used to detect broken glyphs in fonts. By default,
     * FreeType tries to handle broken fonts also.
     *
     * In particular, errors from the TrueType bytecode engine are not passed
     * to the application if this flag is not set; this might result in
     * partially hinted or distorted glyphs in case a glyph's bytecode is
     * buggy.
     */
    const UInt_t PEDANTIC                     = FT_LOAD_PEDANTIC;

    /// This flag is only used internally.
    /*
     *  It merely indicates that the font driver should not load composite
     *  glyphs recursively. Instead, it should set the ‘num_subglyph’ and
     *  ‘subglyphs’ values of the glyph slot accordingly, and set
     *  ‘glyph->format’ to FT_GLYPH_FORMAT_COMPOSITE.
     *
     *  The description of sub-glyphs is not available to client applications
     *  for now.
     *
     *  This flag implies FT_LOAD_NO_SCALE and FT_LOAD_IGNORE_TRANSFORM.
     */
    const UInt_t NO_RECURSE                   = FT_LOAD_NO_RECURSE;

    /// Indicates that the transform matrix set by FT_Set_Transform should be
    /// ignored.
    /*
     *
     */
    const UInt_t IGNORE_TRANSFORM             = FT_LOAD_IGNORE_TRANSFORM;

    /// This flag is used with FT_LOAD_RENDER to indicate that you want to
    /// render an outline glyph to a 1-bit monochrome bitmap glyph, with 8
    /// pixels packed into each byte of the bitmap data.
    /*
     *  Note that this has no effect on the hinting algorithm used. You should
     *  rather use FT_LOAD_TARGET_MONO so that the monochrome-optimized
     *  hinting algorithm is used.
     */
    const UInt_t MONOCHROME                   = FT_LOAD_MONOCHROME;

    /// Indicates that the ‘linearHoriAdvance’ and ‘linearVertAdvance’ fields
    /// of FT_GlyphSlotRec should be kept in font units.
    /*
     *  See FT_GlyphSlotRec for details.
     */
    const UInt_t LINEAR_DESIGN                = FT_LOAD_LINEAR_DESIGN;

    /// Disable auto-hinter.
    /*
     *  See also the note below.
     */
    const UInt_t NO_AUTOHINT                  = FT_LOAD_NO_AUTOHINT;
}


/// An enumeration type that lists the render modes supported by FreeType 2
/**
 *  @see RenderMode
 */
namespace render_mode
{
    /// An enumeration type that lists the render modes supported by FreeType 2
    /**
     *  Each mode corresponds to a specific type of scanline conversion
     *  performed on the outline.
     *
     *  For bitmap fonts and embedded bitmaps the ‘bitmap->pixel_mode’ field in
     *  the FT_GlyphSlotRec structure gives the format of the returned bitmap.
     *
     *  All modes except FT_RENDER_MODE_MONO use 256 levels of opacity.
     *
     *  @note
     *  The LCD-optimized glyph bitmaps produced by FT_Render_Glyph can be
     *  filtered to reduce color-fringes by using FT_Library_SetLcdFilter (not
     *  active in the default builds). It is up to the caller to either call
     *  FT_Library_SetLcdFilter (if available) or do the filtering itself.
     *
     *  The selected render mode only affects vector glyphs of a font. Embedded
     *  bitmaps often have a different pixel mode like FT_PIXEL_MODE_MONO. You
     *  can use FT_Bitmap_Convert to transform them into 8-bit pixmaps.
     */
    enum RenderMode
    {
        /// This is the default render mode; it corresponds to 8-bit
        /// anti-aliased bitmaps.
        NORMAL  = 0,

        /// This is equivalent to FT_RENDER_MODE_NORMAL. It is only defined as
        /// a separate value because render modes are also used indirectly to
        /// define hinting algorithm selectors. See FT_LOAD_TARGET_XXX for
        /// details.
        LIGHT,

        /// This mode corresponds to 1-bit bitmaps (with 2 levels of opacity).
        MONO,

        /// This mode corresponds to horizontal RGB and BGR sub-pixel displays
        /// like LCD screens. It produces 8-bit bitmaps that are 3 times the
        /// width of the original glyph outline in pixels, and which use the
        /// FT_PIXEL_MODE_LCD mode.
        LCD,

        /// This mode corresponds to vertical RGB and BGR sub-pixel displays
        /// (like PDA screens, rotated LCD displays, etc.). It produces 8-bit
        /// bitmaps that are 3 times the height of the original glyph outline
        /// in pixels and use the FT_PIXEL_MODE_LCD_V mode.
        LCD_V,

        /// Max
        MAX
    };
}

/// A list of values that are used to select a specific hinting algorithm to
/// use by the hinter. You should OR one of these values to your ‘load_flags’
/// when calling FT_Load_Glyph.
/**
 *  You should use only one of the FT_LOAD_TARGET_XXX values in your
 *  ‘load_flags’. They can't be ORed.
 *
 *  If FT_LOAD_RENDER is also set, the glyph is rendered in the corresponding
 *   mode (i.e., the mode which matches the used algorithm best). An exeption
 *   is FT_LOAD_TARGET_MONO since it implies FT_LOAD_MONOCHROME.
 *
 *  You can use a hinting algorithm that doesn't correspond to the same
 *  rendering mode. As an example, it is possible to use the ‘light’ hinting
 *  algorithm and have the results rendered in horizontal LCD pixel mode,
 *  with code like
 *
\code
  FT_Load_Glyph( face, glyph_index,
                 load_flags | FT_LOAD_TARGET_LIGHT );

  FT_Render_Glyph( face->glyph, FT_RENDER_MODE_LCD );
\endcode
 *
 */
namespace load_target
{
    template < Int32_t x >
    struct LoadTarget
    {
        static const Int32_t value = (x & 15) << 16;
    };

    /// This corresponds to the default hinting algorithm, optimized for
    /// standard gray-level rendering. For monochrome output, use
    /// FT_LOAD_TARGET_MONO instead.
    const Int32_t   NORMAL = LoadTarget< render_mode::NORMAL>::value;

    /// A lighter hinting algorithm for non-monochrome modes.
    /**
     *  Many generated glyphs are more fuzzy but better resemble its original
     *  shape. A bit like rendering on Mac OS X.
     *
     *  As a special exception, this target implies FT_LOAD_FORCE_AUTOHINT.
     */
    const Int32_t   LIGHT  = LoadTarget< render_mode::LIGHT >::value;

    /// Strong hinting algorithm that should only be used for monochrome
    /// output. The result is probably unpleasant if the glyph is rendered
    /// in non-monochrome modes.
    const Int32_t   MONO   = LoadTarget< render_mode::MONO  >::value;

    /// A variant of FT_LOAD_TARGET_NORMAL optimized for horizontally
    /// decimated LCD displays.
    const Int32_t   LCD    = LoadTarget< render_mode::LCD   >::value;

    /// A variant of FT_LOAD_TARGET_NORMAL optimized for vertically
    /// decimated LCD displays.
    const Int32_t   LCD_V  = LoadTarget< render_mode::LCD_V >::value;
}



/// An enumeration used to specify which kerning values to return in
/// FT_Get_Kerning.
/**
 *  @see KerningMode
 */
namespace kerning_mode
{
    enum KerningMode
    {
        /// Return scaled and grid-fitted kerning distances (value is 0).
        DEFAULT=    0,

        /// Return scaled but un-grid-fitted kerning distances.
        UNFITTED,

        /// Return the kerning vector in original font units.
        UNSCALED
    };
}


/// template used to replace the FT_ENC_TAG macro: converts four-letter
/// tags into an unsigned long type
/**
 * @note Since many 16-bit compilers don't like 32-bit enumerations, you
 *       should redefine this macro in case of problems to something like
 *       this:
 *       @code
#define FT_ENC_TAG( value, _x1, _x2, _x3, _x4 )  value
@endcode
 *       to get a simple enumeration without assigning special numbers.
 */
template < ULong_t x1, ULong_t x2, ULong_t x3, ULong_t x4 >
struct EncTag
{
    static const ULong_t value =
              ( (ULong_t) x1 << 24 )
            | ( (ULong_t) x2 << 16 )
            | ( (ULong_t) x3 <<  8 )
            | ( (ULong_t) x4 <<  0 );
};


/// An enumeration used to specify character sets supported by charmaps. Used
/// in the FT_Select_Charmap API function.
/**
 *  @see Encoding
 */
namespace encoding
{
    /// An enumeration used to specify character sets supported by charmaps.
    /// Used in the FT_Select_Charmap API function.
    /**
     *  Despite the name, this enumeration lists specific character
     *  repertories (i.e., charsets), and not text encoding methods
     *  (e.g., UTF-8, UTF-16, etc.).
     *
     *  Other encodings might be defined in the future.
     *
     *  @note
     *  By default, FreeType automatically synthesizes a Unicode charmap for
     *  PostScript fonts, using their glyph names dictionaries. However, it
     *  also reports the encodings defined explicitly in the font file, for
     *  the cases when they are needed, with the Adobe values as well.
     *
     *  FT_ENCODING_NONE is set by the BDF and PCF drivers if the charmap is
     *  neither Unicode nor ISO-8859-1 (otherwise it is set to
     *  FT_ENCODING_UNICODE). Use FT_Get_BDF_Charset_ID to find out which
     *  encoding is really present. If, for example, the ‘cs_registry’ field
     *  is ‘KOI8’ and the ‘cs_encoding’ field is ‘R’, the font is encoded in
     *  KOI8-R.
     *
     *  FT_ENCODING_NONE is always set (with a single exception) by the
     *  winfonts driver. Use FT_Get_WinFNT_Header and examine the ‘charset’
     *  field of the FT_WinFNT_HeaderRec structure to find out which encoding
     *  is really present. For example, FT_WinFNT_ID_CP1251 (204) means
     *  Windows code page 1251 (for Russian).
     *
     *  FT_ENCODING_NONE is set if ‘platform_id’ is TT_PLATFORM_MACINTOSH and
     *  ‘encoding_id’ is not TT_MAC_ID_ROMAN (otherwise it is set to
     *  FT_ENCODING_APPLE_ROMAN).
     *
     *  If ‘platform_id’ is TT_PLATFORM_MACINTOSH, use the function
     *  FT_Get_CMap_Language_ID to query the Mac language ID which may be
     *  needed to be able to distinguish Apple encoding variants. See
     *
     *  http://www.unicode.org/Public/MAPPINGS/VENDORS/APPLE/README.TXT
     *
     *  to get an idea how to do that. Basically, if the language ID is 0,
     *  don't use it, otherwise subtract 1 from the language ID. Then examine
     *  ‘encoding_id’. If, for example, ‘encoding_id’ is TT_MAC_ID_ROMAN and
     *  the language ID (minus 1) is ‘TT_MAC_LANGID_GREEK’, it is the Greek
     *  encoding, not Roman. TT_MAC_ID_ARABIC with ‘TT_MAC_LANGID_FARSI’ means
     *  the Farsi variant the Arabic encoding.
     */
    enum Encoding
    {
        /// The encoding value 0 is reserved.
        NONE        = EncTag<0,0,0,0>::value,

        /// Corresponds to the Microsoft Symbol encoding, used to encode
        /// mathematical symbols in the 32..255 character code range
        /*
         *  For more information, see ‘http://www.ceviz.net/symbol.htm’.
         */
        MS_SYMBOL   = EncTag<'s','y','m','b'>::value,

        /// Corresponds to the Unicode character set
        /*
         *  This value covers all versions of the Unicode repertoire,
         *  including ASCII and Latin-1. Most fonts include a Unicode charmap,
         *  but not all of them.
         *
         *  For example, if you want to access Unicode value U+1F028 (and the
         *  font contains it), use value 0x1F028 as the input value for
         *  FT_Get_Char_Index.
         */
        UNICODE     = EncTag<'u','n','i','c'>::value,

        /// Corresponds to Japanese SJIS encoding
        /*
         *  More info at at
         *  ‘http://langsupport.japanreference.com/encoding.shtml’.
         *  See note on multi-byte encodings below.
         */
        SJIS        = EncTag<'s','j','i','s'>::value,

        /// Corresponds to an encoding system for Simplified Chinese as used
        /// used in mainland China.
        /*
         *
         */
        GB2312      = EncTag<'g','b',' ',' '>::value,

        /// Corresponds to an encoding system for Traditional Chinese as used
        /// in Taiwan and Hong Kong.
        /*
         *
         */
        BIG5        = EncTag<'b','i','g','5'>::value,

        /// Corresponds to the Korean encoding system known as Wansung
        /*
         *  For more information see
         *  ‘http://www.microsoft.com/typography/unicode/949.txt’.
         */
        WANSUNG     = EncTag<'w','a','n','s'>::value,

        /// The Korean standard character set (KS C 5601-1992), which
        /// corresponds to MS Windows code page 1361
        /*
         *  This character set includes all possible Hangeul character
         *  combinations.
         */
        JOHAB       = EncTag<'j','o','h','a'>::value,

        /// Corresponds to the Adobe Standard encoding, as found in Type 1,
        /// CFF, and OpenType/CFF fonts.
        /**
         *  It is limited to 256 character codes.
         */
        ADOBE_STANDARD  = EncTag<'A','D','O','B'>::value,

        /// Corresponds to the Adobe Expert encoding, as found in Type 1,
        /// CFF, and OpenType/CFF fonts
        /*
         *  It is limited to 256 character codes.
         */
        ADOBE_EXPERT    = EncTag<'A','D','B','E'>::value,

        /// Corresponds to a custom encoding, as found in Type 1, CFF, and
        /// OpenType/CFF fonts.
        /*
         *  It is limited to 256 character codes.
         */
        ADOBE_CUSTOM    = EncTag<'A','D','B','C'>::value,

        /// Corresponds to a Latin-1 encoding as defined in a Type 1
        /// PostScript font.
        /*
         *  It is limited to 256 character codes.
         */
        ADOBE_LATIN_1   = EncTag<'l','a','t','1'>::value,

        /// This value is deprecated and was never used nor reported by
        /// FreeType. Don't use or test for it.
        OLD_LATIN_2     = EncTag<'l','a','t','2'>::value,

        /// Corresponds to the 8-bit Apple roman encoding
        /*
         *  Many TrueType and OpenType fonts contain a charmap for this
         *  encoding, since older versions of Mac OS are able to use it
         */
        APPLE_ROMAN     = EncTag<'a', 'r', 'm', 'n'>::value
    };
}

typedef encoding::Encoding Encoding;


/// A list of constants used to describe subglyphs. Please refer to the
/// TrueType specification for the meaning of the various flags.
namespace subglyph_flag
{
    const UInt32_t ARGS_ARE_WORDS           = 1;
    const UInt32_t ARGS_ARE_XY_VALUES       = 2;
    const UInt32_t ROUND_XY_TO_GRID         = 4;
    const UInt32_t SCALE                    = 8;
    const UInt32_t XY_SCALE              = 0x40;
    const UInt32_t _2X2                  = 0x80;
    const UInt32_t USE_MY_METRICS       = 0x200;
}


/// A list of constants used to describe curve tags
namespace curve_tag
{
    const UInt  ON    = FT_CURVE_TAG_ON;
    const UInt  CONIC = FT_CURVE_TAG_CONIC;
    const UInt  CUBIC = FT_CURVE_TAG_CUBIC;

    const UInt  DROPOUT_MASK    = 0xE0;
    const UInt  DROPOUT_SHIFT   = 5;
}


/// A list of bit flags used in the ‘fsType’ field of the OS/2 table in a
/// TrueType or OpenType font and the ‘FSType’ entry in a PostScript font.
/**
 *  These bit flags are returned by FT_Get_FSType_Flags; they inform client
 *  applications of embedding and subsetting restrictions associated with a
 *  font.
 *
 *  See http://www.adobe.com/devnet/acrobat/pdfs/FontPolicies.pdf for more
 *  details.
 *
 *  @note
 *  While the fsType flags can indicate that a font may be embedded, a license
 *  with the font vendor may be separately required to use the font in this way.
 */
namespace fstype
{
    /// Fonts with no fsType bit set may be embedded and permanently installed
    /// on the remote system by an application.
    const UShort_t INSTALLABLE_EMBEDDING          = 0x0000;

    /// Fonts that have only this bit set must not be modified, embedded or
    /// exchanged in any manner without first obtaining permission of the font
    /// software copyright owner.
    const UShort_t RESTRICTED_LICENSE_EMBEDDING   = 0x0002;

    /// If this bit is set, the font may be embedded and temporarily loaded on
    /// the remote system. Documents containing Preview & Print fonts must be
    /// opened ‘read-only’; no edits can be applied to the document.
    const UShort_t PREVIEW_AND_PRINT_EMBEDDING    = 0x0004;

    /// If this bit is set, the font may be embedded but must only be
    /// installed temporarily on other systems. In contrast to Preview & Print
    /// fonts, documents containing editable fonts may be opened for reading,
    /// editing is permitted, and changes may be saved.
    const UShort_t EDITABLE_EMBEDDING             = 0x0008;

    /// If this bit is set, the font may not be subsetted prior to embedding.
    const UShort_t NO_SUBSETTING                  = 0x0100;

    /// If this bit is set, only bitmaps contained in the font may be
    /// embedded; no outline data may be embedded. If there are no bitmaps
    /// available in the font, then the font is unembeddable.
    const UShort_t BITMAP_EMBEDDING_ONLY          = 0x0200;
}

/// namespace wrapper for SizeRequestType
/**
 *  @see SizeRequestType
 */
namespace size_request_type
{
    /// An enumeration type that lists the supported size request types.
    /**
     *  @note   The above descriptions only apply to scalable formats. For
     *          bitmap formats, the behaviour is up to the driver.
     *
     *          See the note section of FT_Size_Metrics if you wonder how
     *          size requesting relates to scaling values.
     */
    enum SizeRequestType
    {
        NOMINAL,    ///< The nominal size. The ‘units_per_EM’ field of
                    ///  FT_FaceRec is used to determine both scaling values.
        REAL_DIM,   ///< The real dimension. The sum of the the ‘ascender’ and
                    ///  (minus of) the ‘descender’ fields of FT_FaceRec are
                    ///  used to determine both scaling values.
        BBOX,       ///< The font bounding box. The width and height of the
                    ///  ‘bbox’ field of FT_FaceRec are used to determine the
                    ///  horizontal and vertical scaling value, respectively.
        CELL,       ///< The ‘max_advance_width’ field of FT_FaceRec is used
                    ///  to determine the horizontal scaling value; the
                    ///  vertical scaling value is determined the same way as
                    ///  FT_SIZE_REQUEST_TYPE_REAL_DIM does. Finally, both
                    ///  scaling values are set to the smaller one. This type
                    ///  is useful if you want to specify the font size for,
                    ///  say, a window of a given dimension and 80x24 cells.
        SCALES,     ///< Specify the scaling values directly.
        MAX         ///< MAX
    };
}

typedef size_request_type::SizeRequestType SizeRequestType;



}














#endif // CPPFREETYPE_H_
