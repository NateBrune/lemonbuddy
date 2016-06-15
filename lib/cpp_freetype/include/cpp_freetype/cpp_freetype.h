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
 *  \file   include/cppfreetype/cppfreetype.h
 *
 *  \date   Aug 1, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef CPPFREETYPE_CPPFREETYPE_H_
#define CPPFREETYPE_CPPFREETYPE_H_

#include <cpp_freetype/AssignmentPair.h>
#include <cpp_freetype/RefPtr.h>
#include <cpp_freetype/CPtr.h>

#include <cpp_freetype/types.h>
#include <cpp_freetype/Face.h>
#include <cpp_freetype/GlyphSlot.h>
#include <cpp_freetype/Library.h>
#include <cpp_freetype/Outline.h>
#include <cpp_freetype/Untag.h>


/// root namespace for freetype
namespace freetype
{
    /// Initialize a new FreeType library object. The set of modules that are
    /// registered by this function is determined at build time.
    /**
     * @return      A handle to a new library object
     *
     * @note    In case you want to provide your own memory allocating
     *          routines, use Library::new instead, followed by a call to
     *          Library::add_default_modules (or a series of calls to
     *          Library::add_module).
     *
     * @note    For multi-threading applications each thread should have its
     *          own Library object.
     *
     * @note    when using this function, it is expected that the library is
     *          destroyed with freetype::done. This is becasue freetype::init
     *          creates a memory manager and gives it a reference count, and
     *          when we call ~Library it only decrements the library count,
     *          not the reference count. Therefore, make sure you call
     *          freetype::done on the main library instance prior to it
     *          going out of scope
     *
     * @note    this version silently ignores any error result, see init_e
     *          for a function which returns an error code as well
     */
    RefPtr<Library> init();

    /// Initialize a new FreeType library object. The set of modules that are
    /// registered by this function is determined at build time.
    /**
     * @return  A handle to a new library object, and the result of the
     *          underlyinig call
     *
     * @note    In case you want to provide your own memory allocating
     *          routines, use Library::new instead, followed by a call to
     *          Library::add_default_modules (or a series of calls to
     *          Library::add_module).
     *
     * @note    For multi-threading applications each thread should have its
     *          own Library object.
     *
     * @note    when using this function, it is expected that the library is
     *          destroyed with freetype::done. This is becasue freetype::init
     *          creates a memory manager and gives it a reference count, and
     *          when we call ~Library it only decrements the library count,
     *          not the reference count. Therefore, make sure you call
     *          freetype::done on the main library instance prior to it
     *          going out of scope
     */
    RValuePair< RefPtr<Library>, Error > init_e();

    /// Destroy a given FreeType library object and all of its children,
    /// including resources, drivers, faces, sizes, etc.
    /**
     *  @param[in]  library     handle to the library object to destroy,
     *                          must have been created with freetype::init
     *  @return FeeType error code. 0 means success
     *
     *  @note   Since this function decements the reference count of the
     *          library, it will alter the library object changing it's
     *          underlying pointer to null, so that the handle becomes
     *          invalid
     */
    Error_t done(RefPtr<Library>& library);


}

#endif // CPPFREETYPE_H_
