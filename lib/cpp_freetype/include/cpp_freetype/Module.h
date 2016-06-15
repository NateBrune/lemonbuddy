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
 *  \file   include/cppfreetype/Module.h
 *
 *  \date   Aug 1, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#ifndef CPPFREETYPE_MODULE_H_
#define CPPFREETYPE_MODULE_H_

namespace freetype
{

class Module
{
    private:
        void*   m_ptr;

    public:
        /// wrap constructor, \p ptr must be a FT_Module
        /**
         *  @param[in]  ptr         pointer to underlying object which is to
         *                          be wrapped
         */
        Module( void* ptr  );

        /// return underlying pointer
        void* get_ptr();

        /// returns true if contained pointer is not null
        bool is_valid();
};

} // namespace freetype 

#endif // MODULE_H_
