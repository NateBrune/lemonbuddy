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
 *  \file   include/cppfreetype/OpenArgs.h
 *
 *  \date   Aug 1, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef CPPFREETYPE_OPENARGS_H_
#define CPPFREETYPE_OPENARGS_H_

#include <cpp_freetype/types.h>
#include <cpp_freetype/Module.h>

namespace freetype
{


/// A structure used to indicate how to open a new font file or stream. A
/// pointer to such a structure can be used as a parameter for the functions
/// Open_Face_t& and Attach_Stream_t&.
/**
 *  The stream type is determined by the contents of ‘flags’ which are tested
 *  in the following order by FT_Open_Face:
 *
 *  If the ‘FT_OPEN_MEMORY’ bit is set, assume that this is a memory file of
 *  ‘memory_size’ bytes, located at ‘memory_address’. The data are are not
 *  copied, and the client is responsible for releasing and destroying them
 *  after the corresponding call to FT_Done_Face.
 *
 *  Otherwise, if the ‘FT_OPEN_STREAM’ bit is set, assume that a custom input
 *  stream ‘stream’ is used.
 *
 *  Otherwise, if the ‘FT_OPEN_PATHNAME’ bit is set, assume that this is a
 *  normal file and use ‘pathname’ to open it.
 *
 *  If the ‘FT_OPEN_DRIVER’ bit is set, FT_Open_Face only tries to open the
 *  file with the driver whose handler is in ‘driver’.
 *
 *  If the ‘FT_OPEN_PARAMS’ bit is set, the parameters given by ‘num_params’
 *  and ‘params’ is used. They are ignored otherwise.
 *
 *  Ideally, both the ‘pathname’ and ‘params’ fields should be tagged as
 *  ‘const’; this is missing for API backwards compatibility. In other words,
 *  applications should treat them as read-only.
 *
 *   */
class OpenArgs
{
    private:
        void* m_ptr;    ///< pointer to the underlying object

    public:
        /// A set of bit flags indicating how to use the structure.
        UInt_t&         flags();

        /// The first byte of the file in memory.
        const Byte_t*&  memory_base();

        /// The size in bytes of the file in memory.
        Long_t&         memory_size();

        /// A pointer to an 8-bit file pathname.
        String_t*&      pathname();

        /// A handle to a source stream object.
        //Stream&        stream;

        /// This field is exclusively used by FT_Open_Face; it simply
        /// specifies the font driver to use to open the face. If set to 0,
        /// FreeType tries to load the face with each one of the drivers in
        /// its list.
        Module&         driver();

        /// The number of extra parameters.
        Int_t&          num_params();

        /// Extra parameters passed to the font driver when opening a new face.
        //Parameter*&     params();
};

} // namespace freetype 

#endif // OPENARGS_H_
