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
 *  @file   include/cppfreetype/RefPtr.h
 *
 *  @date   Feb 3, 2013
 *  @author Josh Bialkowski (jbialk@mit.edu)
 *  @brief  
 */

#ifndef CPPFREETYPE_REFPTR_H_
#define CPPFREETYPE_REFPTR_H_

#include <cpp_freetype/AssignmentPair.h>
#include <cpp_freetype/CPtr.h>


namespace freetype {

/// pointer to a reference counted object, auto destruct when reference
/// count is zero
template< class Traits >
class RefPtr
{
    public:
        typedef typename Traits::cobjptr    cobjptr;
        typedef typename Traits::Delegate   Delegate;
        typedef typename Traits::Storage    Storage;

    private:
        Storage m_ptr;

        /// increase reference count by one, see specializations
        void reference(){}

        /// decrease reference count by one, see specializations
        void dereference(){}


    public:
        /// create a RefPtr from the specified cobj
        /**
         *  @param ptr      the c-obj pointer to wrap
         *  @param doRef    whether or not to increase the reference count
         *
         *  @note since freetype sometimes gives us a pointer which already has
         *        a reference count of 1, @p reference defaults to false.
         */

        explicit RefPtr( cobjptr ptr=0, bool doRef=false ):
            m_ptr(ptr)
        {
            if(doRef)
                reference();
        }

        /// copy construct a pointer, increasing the reference count
        RefPtr( const RefPtr<Traits>& other ):
            m_ptr(other.m_ptr)
        {
            reference();
        }

        /// when the RefPtr is destroyed the reference count of the pointed-to
        /// object is decreased
        ~RefPtr()
        {
            dereference();
        }

        /// dereference the stored object and turn this into a null pointer
        void unlink()
        {
            dereference();
            m_ptr = 0;
        }

        /// return the stored pointer, subverting reference safety, see
        /// specializations if Storage is not the same as cobjptr
        cobjptr subvert()
        {
            return m_ptr;
        }

        const cobjptr subvert() const
        {
            return m_ptr;
        }

        /// assignment operator, decreases reference count of current object,
        /// increases reference count of copied pointer
        RefPtr<Traits>& operator=( const RefPtr<Traits>& other )
        {
            dereference();
            m_ptr = other.m_ptr;
            reference();
            return *this;
        }

        /// the member operator, exposes the underlying cobj pointer
        Delegate operator->()
        {
            return Delegate(m_ptr);
        }

        const Delegate operator->() const
        {
            return Delegate(m_ptr);
        }

        CPtr<Traits> operator*()
        {
            return CPtr<Traits>(m_ptr);
        }

        ConstCPtr<Traits> operator*() const
        {
            return ConstCPtr<Traits>(m_ptr);
        }

        operator bool() const
        {
            return m_ptr;
        }

        template <typename T2>
        LValuePair< RefPtr<Traits>,T2 > operator,( T2& other )
        {
            return LValuePair< RefPtr<Traits>,T2 >(*this,other);
        }

};


} // namespace cppfreetype




#endif // REFPTR_H_
