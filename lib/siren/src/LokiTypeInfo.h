/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/**************************************************************** siren-cpr beg
 *
 * siren - flexible 3D game engine
 * siren is (C) Copyright 2003 by members of the
 *    Iowa State University Game Developers Club
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: LokiTypeInfo.h,v $
 * Date modified: $Date: 2003-01-02 04:18:17 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
////////////////////////////////////////////////////////////////////////////////
// The Loki Library
// Copyright (c) 2001 by Andrei Alexandrescu
// This code accompanies the book:
// Alexandrescu, Andrei. "Modern C++ Design: Generic Programming and Design 
//     Patterns Applied". Copyright (c) 2001. Addison-Wesley.
// Permission to use, copy, modify, distribute and sell this software for any 
//     purpose is hereby granted without fee, provided that the above copyright 
//     notice appear in all copies and that both that copyright notice and this 
//     permission notice appear in supporting documentation.
// The author or Addison-Welsey Longman make no representations about the 
//     suitability of this software for any purpose. It is provided "as is" 
//     without express or implied warranty.
////////////////////////////////////////////////////////////////////////////////

// Last update: May 19, 2002

#ifndef TYPEINFO_INC_
#define TYPEINFO_INC_

#include <typeinfo>
#include <cassert>

namespace Loki
{
////////////////////////////////////////////////////////////////////////////////
// class TypeInfo
// Purpose: offer a first-class, comparable wrapper over std::type_info
////////////////////////////////////////////////////////////////////////////////

    class TypeInfo
    {
    public:
        // Constructors
        TypeInfo(); // needed for containers
        TypeInfo(const std::type_info&); // non-explicit

        // Access for the wrapped std::type_info
        const std::type_info& Get() const;
        // Compatibility functions
        bool before(const TypeInfo& rhs) const;
        const char* name() const;

    private:
        const std::type_info* pInfo_;
    };
    
// Implementation
    
    inline TypeInfo::TypeInfo()
    {
        class Nil {};
        pInfo_ = &typeid(Nil);
        assert(pInfo_);
    }
    
    inline TypeInfo::TypeInfo(const std::type_info& ti)
    : pInfo_(&ti)
    { assert(pInfo_); }
    
    inline bool TypeInfo::before(const TypeInfo& rhs) const
    {
        assert(pInfo_);
        return pInfo_->before(*rhs.pInfo_) != 0;
    }

    inline const std::type_info& TypeInfo::Get() const
    {
        assert(pInfo_);
        return *pInfo_;
    }
    
    inline const char* TypeInfo::name() const
    {
        assert(pInfo_);
        return pInfo_->name();
    }

// Comparison operators
    
    inline bool operator==(const TypeInfo& lhs, const TypeInfo& rhs)
    { return (lhs.Get() == rhs.Get()) != 0; }

    inline bool operator<(const TypeInfo& lhs, const TypeInfo& rhs)
    { return lhs.before(rhs); }

    inline bool operator!=(const TypeInfo& lhs, const TypeInfo& rhs)
    { return !(lhs == rhs); }    
    
    inline bool operator>(const TypeInfo& lhs, const TypeInfo& rhs)
    { return rhs < lhs; }
    
    inline bool operator<=(const TypeInfo& lhs, const TypeInfo& rhs)
    { return !(lhs > rhs); }
     
    inline bool operator>=(const TypeInfo& lhs, const TypeInfo& rhs)
    { return !(lhs < rhs); }
}

////////////////////////////////////////////////////////////////////////////////
// Change log:
// June 20, 2001: ported by Nick Thurn to gcc 2.95.3. Kudos, Nick!!!
// May  10, 2002: ported by Rani Sharoni to VC7 (RTM - 9466)
////////////////////////////////////////////////////////////////////////////////

#endif // TYPEINFO_INC_
