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
 *  @file   include/cppfreetype/CPtr.h
 *
 *  @date   Feb 5, 2013
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  
 */

#ifndef CPPFREETYPE_CPTR_H_
#define CPPFREETYPE_CPTR_H_


namespace freetype {

template< class Traits > class RefPtr;

/// acts like a c-pointer by overloading the ->() operator, but is not
/// copyable and doesn't allow the underlying c-pointer to be copied
template< class Traits >
class CPtr
{
    public:
        typedef typename Traits::cobjptr  cobjptr;

    private:
        cobjptr m_ptr;

        /// may only be constructed by a RefPtr
        explicit CPtr(cobjptr ptr=0):
            m_ptr(ptr)
        {}

        /// not construction-copyable
        CPtr( const CPtr<Traits>& other );

        /// not copyable
        CPtr<Traits>& operator=( const CPtr<Traits>& );

    public:
        friend class RefPtr<Traits>;

        cobjptr operator->()
        {
            return m_ptr;
        }

        const cobjptr operator->() const
        {
            return m_ptr;
        }
};


/// acts like a const c-pointer by overloading the ->() operator, but is not
/// copyable and doesn't allow the underlying c-pointer to be copied
template< class Traits >
class ConstCPtr
{
    public:
        typedef typename Traits::cobjptr cobjptr;

    private:
        const cobjptr m_ptr;

        /// may only be constructed by a RefPtr
        explicit ConstCPtr(const cobjptr ptr=0):
            m_ptr(ptr)
        {}

        /// not construction-copyable
        ConstCPtr( const ConstCPtr<Traits>& other );

        /// not copyable
        ConstCPtr<Traits>& operator=( const ConstCPtr<Traits>& );

    public:
        friend class RefPtr<Traits>;

        const cobjptr operator->() const
        {
            return m_ptr;
        }
};


} // namespace cppfreetype


#endif // CPTR_H_
