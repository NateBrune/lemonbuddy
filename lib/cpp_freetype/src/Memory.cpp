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
 *  \file   src/Memory.cpp
 *
 *  \date   Aug 1, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include <cpp_freetype/Memory.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MODULE_H

extern "C"
{

void* cpp_freetype_alloc( FT_Memory memory, long size );

void  cpp_freetype_free( FT_Memory memory, void* block );

void* cpp_freetype_realloc( FT_Memory memory,
                            long cur_size,
                            long new_size,
                            void* block);

}


namespace freetype
{

struct MemorySlots
{
    AllocFunc_t     alloc;
    FreeFunc_t      free;
    ReallocFunc_t   realloc;
};

}

void* cpp_freetype_alloc( FT_Memory memory, long size )
{
    using namespace freetype;
    MemorySlots* slots = (MemorySlots*)( memory->user );
    return (slots->alloc)(size);
}

void  cpp_freetype_free( FT_Memory memory, void* block )
{
    using namespace freetype;
    MemorySlots* slots = (MemorySlots*)( memory->user );
    return (slots->free)(block);
}

void* cpp_freetype_realloc( FT_Memory memory,
                            long cur_size,
                            long new_size,
                            void* block)
{
    using namespace freetype;
    MemorySlots* slots = (MemorySlots*)( memory->user );
    return (slots->realloc)(cur_size, new_size, block);
}

namespace freetype
{


Memory::Memory( void* ptr )
{
    m_ptr = ptr;
}

void* Memory::get_ptr()
{
    return m_ptr;
}

void Memory::destroy()
{
    if(m_ptr)
    {
        FT_Memory       memory  = (FT_Memory)m_ptr;
        MemorySlots*    slots   = (MemorySlots*)memory->user;
        delete memory;
        delete slots;
        m_ptr = 0;
    }
}


Memory Memory::create(  AllocFunc_t     alloc,
                        FreeFunc_t      free,
                        ReallocFunc_t   realloc )
{
    MemorySlots* slots = new MemorySlots;
    slots->alloc    = alloc;
    slots->free     = free;
    slots->realloc  = realloc;

    FT_Memory memory = new FT_MemoryRec_;
    memory->user    = (void*)slots;
    memory->alloc   = &cpp_freetype_alloc;
    memory->free    = &cpp_freetype_free;
    memory->realloc = &cpp_freetype_realloc;

    return Memory(memory);
}







} // namespace freetype 
