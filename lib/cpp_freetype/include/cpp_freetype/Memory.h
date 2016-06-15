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
 *  \file   include/cppfreetype/Memory.h
 *
 *  \date   Aug 1, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef CPPFREETYPE_MEMORY_H_
#define CPPFREETYPE_MEMORY_H_

#include <cpp_freetype/types.h>

namespace freetype
{


/// A handle to a given memory manager object, defined with an
/// FT_MemoryRec structure.
/**
 *  @note   Memory managers are not reference counted, and ownership is not
 *          assumed by freetype. Destroy the underlying object with
 *          Memory::destroy when you are finished with it
 */
class Memory
{
    private:
        void* m_ptr;

    public:
        /// Wrap constructor,
        Memory( void* ptr );

        /// return underyling FT_Memory handle
        void* get_ptr();

        /// destroys the underlying FT_Memory object, make sure it is only
        /// called on one copy of the handle
        void destroy();

        /// create a new memory management handle which wraps the
        /// provided memory management slots
        static Memory create(   AllocFunc_t     alloc,
                                FreeFunc_t      free,
                                ReallocFunc_t   realloc );

};





} // namespace freetype 

#endif // MEMORY_H_
