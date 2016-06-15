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
 *  \file   include/cppfreetype/Library.h
 *
 *  \date   Aug 1, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef CPPFREETYPE_LIBRARY_H_
#define CPPFREETYPE_LIBRARY_H_

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MODULE_H

#include <cpp_freetype/RefPtr.h>
#include <cpp_freetype/types.h>
#include <cpp_freetype/Face.h>
#include <cpp_freetype/Memory.h>
#include <cpp_freetype/Module.h>
#include <cpp_freetype/ModuleClass.h>
#include <cpp_freetype/OpenArgs.h>

namespace freetype
{

class Library;

/// c++ interface on top of c-object pointer
class LibraryDelegate
{
    private:
        FT_Library  m_ptr;

        /// constructable only by RefPtr<Library>
        LibraryDelegate( FT_Library ptr=0 ):
            m_ptr(ptr)
        {}

        /// not cop-constructable
        LibraryDelegate( const LibraryDelegate& );

        /// not copy-assignable
        LibraryDelegate& operator=( const LibraryDelegate& );

    public:
        friend class RefPtr<Library>;

        LibraryDelegate* operator->(){ return this; }
        const LibraryDelegate* operator->() const{ return this; }

        /// Add the set of default drivers to a given library object.
        /**
         *  This is only useful when you create a library object with
         *  Library::create (usually to plug a custom memory manager).
         */
        void add_default_modules();

        /// Add a new module to a given library instance.
        /**
         *  @param[in]  clazz   pointer to the class descriptor for the
         *                      module
         *  @return FreeType error code. 0 means success
         *
         *  @note   An error will be returned if a module already exists by
         *          that name, or if the module requires a version of
         *          FreeType that is too great.
         */
//        Error_t add_module( const ModuleClass& clazz );

        /// Find a module by it's name
        /**
         *  @param[in]  module_name     The module's name (as an ASCII string)
         *  @return     A module handle. 0 if none was found.
         *
         *  @note   FreeType's internal modules aren't documented very well,
         *          and you should look up the source code for details.
         */
//        Module get_module( const char* module_name );

        /// Remove a given module from a library instance
        /**
         *  @param[in]  module  a handle to a module object
         *  @return FreeType error code. 0 means success
         *
         *  @note   The module object is destroyed by the function in case of
         *          success
         */
//        Error_t remove_module( Module module );

        /// calls Library::open_face to open a font by it's pathname
        /**
         * @param[in]   filepath    path of the font file
         * @param[in]   face_index  index of the face within the font, 0 indexed
         * @return  A handle to a new face object. If `face_index` is greater
         *          than or equal to zro, it must be non-NULL. See
         *          Library::open_face for more details
         */
        RefPtr<Face> new_face(  const char* filepath,
                                Long        face_index );

        /// calls Library::open_face to open a font by it's pathname
        /**
         * @param[in]   filepath    path of the font file
         * @param[in]   face_index  index of the face within the font, 0 indexed
         * @return  A handle to a new face object. If `face_index` is greater
         *          than or equal to zro, it must be non-NULL. See
         *          Library::open_face for more details
         */
        RValuePair< RefPtr<Face>, Error> new_face_e(
                                const char* filepath,
                                Long        face_index );

        /// Create a face object from a given resource described by
        /// FT_Open_Args.
        /**
         *  @param[in]  args        A pointer to an ‘FT_Open_Args’ structure
         *                          which must be filled by the caller.
         *  @param[in]  face_index  The index of the face within the font. The
         *                          first face has index 0.
         *  @param[out] error       FreeType error code. 0 means success.
         *  @return A handle to a new face object. If ‘face_index’ is greater
         *          than or equal to zero, it must be non-NULL. See note below.
         *
         *  Unlike FreeType 1.x, this function automatically creates a glyph
         *  slot for the face object which can be accessed directly through
         *  ‘face->glyph’.
         *
         *  FT_Open_Face can be used to quickly check whether the font format
         *  of a given font resource is supported by FreeType. If the
         *  ‘face_index’ field is negative, the function's return value is
         *  0 if the font format is recognized, or non-zero otherwise; the
         *  function returns a more or less empty face handle in ‘*aface’ (if
         *  ‘aface’ isn't NULL). The only useful field in this special case
         *  is ‘face->num_faces’ which gives the number of faces within the
         *  font file. After examination, the returned FT_Face structure
         *  should be deallocated with a call to FT_Done_Face.
         *
         *  Each new face object created with this function also owns a
         *  default FT_Size object, accessible as ‘face->size’.
         *
         *  One FT_Library instance can have multiple face objects, this is,
         *  FT_Open_Face and its siblings can be called multiple times using
         *  the same ‘library’ argument.
         *
         *  See the discussion of reference counters in the description of
         *  FT_Reference_Face.
         */
//        Face open_face( const OpenArgs& args,
//                        Long_t          face_index,
//                        Error_t&        error );

};

/// traits class for Library, a FreeType library instance
/**
 *  Each ‘library’ is completely independent from the others; it is the ‘root’
 *  of a set of objects like fonts, faces, sizes, etc.
 *
 *  It also embeds a memory manager (see FT_Memory), as well as a scan-line
 *  converter object (see FT_Raster).
 *
 *  For multi-threading applications each thread should have its own
 *  FT_Library object.
 *
 *  @note   The underlying FT_Library object is reference counted, so there
 *          is an appropriate copy and assignment constructor for this class.
 *          As such, you should probably not pass around pointers to a Library
 *          object
 */
struct Library
{
    typedef LibraryDelegate Delegate;
    typedef FT_Library      Storage;
    typedef FT_Library      cobjptr;

    /// This function is used to create a new FreeType library instance
    /// from a given memory object.
    /**
     *  It is thus possible to use libraries with distinct memory
     *  allocators within the same program.
     *
     *  Normally, you would call this function (followed by a call to
     *  FT_Add_Default_Modules or a series of calls to FT_Add_Module)
     *  instead of FT_Init_FreeType to initialize the FreeType library.
     *
     *  Don't use freetype::done but Library::done to destroy a
     *  library instance.
     *
     *  @param[in]  memory  A handle to the original memory object
     *  @param[out] error   FreeType error code. 0 means success
     *  @return     A handle to a new library object
     *  @note       See the discussion of reference counters in the
     *              description of FT_Reference_Library.
     */
    //static RefPtr<Library> create( RefPtr<Memory> memory, Error_t& error );
};






} // namespace freetype 

#endif // LIBRARY_H_
