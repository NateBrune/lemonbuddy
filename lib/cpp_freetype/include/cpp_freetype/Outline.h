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
 *  @file   include/cppfreetype/Outline.h
 *
 *  @date   Feb 5, 2013
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  
 */

#ifndef CPPFREETYPE_OUTLINE_H_
#define CPPFREETYPE_OUTLINE_H_

#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_MODULE_H

#include <cpp_freetype/types.h>
#include <cpp_freetype/RefPtr.h>

namespace freetype {

class Outline;


struct PointReference
{
    FT_Outline* m_outline;  ///< outline we're iterating over
    Int         m_i;        ///< index of the point we're on

    PointReference( FT_Outline* outline, Int i);
    Pos x();
    Pos y();
    bool on();
    bool off();
    bool conic();
    bool cubic();
};

struct PointIterator:
    PointReference
{
    PointIterator( FT_Outline* outline=0, Int i=0);
    PointReference* operator->();
    PointReference& operator*();
    PointIterator& operator++();
    PointIterator& operator--();
    bool operator!=( const PointIterator& other );
};

struct ContourReference
{
    FT_Outline* m_outline;  ///< outline we're iterating over
    Int_t       m_i;        ///< index of the contour we're on

    ContourReference( FT_Outline* outline, Int i);
    PointIterator begin();
    PointIterator end();
};

struct ContourIterator:
    private ContourReference
{
    ContourIterator( FT_Outline* outline=0, Int_t i=0 );
    ContourReference* operator->();
    ContourReference& operator*();
    ContourIterator& operator++();
    ContourIterator& operator--();
    UInt16_t    size();
    bool done();
    bool operator!=( const ContourIterator& other );
};



class OutlineDelegate
{
    private:
        FT_Outline* m_ptr;

        /// constructable only by RefPtr<Outline>
        OutlineDelegate( FT_Outline* ptr=0 ):
            m_ptr(ptr)
        {}

        /// not copy-constructable
        OutlineDelegate( const OutlineDelegate& );

        /// not copy-assignable
        OutlineDelegate& operator=( const OutlineDelegate& );

    public:
        friend class RefPtr<Outline>;

        OutlineDelegate* operator->(){ return this; }
        const OutlineDelegate* operator->() const{ return this; }

        ContourIterator begin();
        ContourIterator end();

        Short   n_contours() const;
        Short   n_points()   const;



};

struct Outline
{
    typedef OutlineDelegate    Delegate;
    typedef FT_Outline*        Storage;
    typedef FT_Outline*        cobjptr;
};


}















#endif // OUTLINE_H_
