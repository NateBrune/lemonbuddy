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
 *  @file   src/Outline.cpp
 *
 *  @date   Feb 5, 2013
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  
 */

#include <cpp_freetype/Outline.h>

namespace freetype {

PointReference::PointReference( FT_Outline* outline, Int i):
    m_outline(outline),
    m_i(i)
{}

Pos PointReference::x()
{
    return m_outline->points[m_i].x;
}

Pos PointReference::y()
{
    return m_outline->points[m_i].y;
}

bool PointReference::on()
{
    return (m_outline->tags[m_i] & 0x03) == curve_tag::ON;
}

bool PointReference::off()
{
    return !on();
}

bool PointReference::conic()
{
    return (m_outline->tags[m_i] & 0x03) == curve_tag::CONIC;
}

bool PointReference::cubic()
{
    return (m_outline->tags[m_i] & 0x03) == curve_tag::CUBIC;
}

PointIterator::PointIterator( FT_Outline* outline, Int i):
    PointReference(outline,i)
{}

PointReference* PointIterator::operator->()
{
    return this;
}

PointReference& PointIterator::operator*()
{
    return *this;
}

PointIterator& PointIterator::operator++()
{
    ++m_i;
    return *this;
}

PointIterator& PointIterator::operator--()
{
    --m_i;
    return *this;
}

bool PointIterator::operator!=( const PointIterator& other )
{
    return m_i != other.m_i;
}

ContourReference::ContourReference( FT_Outline* outline, Int i):
    m_outline(outline),
    m_i(i)
{}

PointIterator ContourReference::begin()
{
    if(m_i > 0)
        return PointIterator(m_outline,m_outline->contours[m_i-1]+1);
    else
        return PointIterator(m_outline,0);
}

PointIterator ContourReference::end()
{
    return PointIterator(m_outline,m_outline->contours[m_i]+1);
}

ContourIterator::ContourIterator( FT_Outline* outline, Int_t i ):
        ContourReference(outline,i)
{}

ContourReference* ContourIterator::operator->()
{
    return this;
}

ContourReference& ContourIterator::operator*()
{
    return *this;
}

ContourIterator& ContourIterator::operator++()
{
    ++m_i;
    return *this;
}

ContourIterator& ContourIterator::operator--()
{
    --m_i;
    return *this;
}

UInt16_t ContourIterator::size()
{
    if( m_i == 0 )
        return m_outline->contours[0]+1;
    else
        return m_outline->contours[m_i] - m_outline->contours[m_i-1];
}

bool ContourIterator::done()
{
    return m_i >= m_outline->n_contours;
}

bool ContourIterator::operator!=( const ContourIterator& other )
{
    return m_i != other.m_i;
}

ContourIterator OutlineDelegate::begin()
{
    return ContourIterator(m_ptr);
}

ContourIterator OutlineDelegate::end()
{
    return ContourIterator(m_ptr,m_ptr->n_contours);
}

Short   OutlineDelegate::n_contours() const
{
    return m_ptr->n_contours;
}

Short   OutlineDelegate::n_points()   const
{
    return m_ptr->n_points;
}





}







