
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     ContextData.h     =-
//
//  Define.h: a class to map data to contexts
//
/////////////////// <GK heading BEGIN do not edit this line> /////////////////
//
// gamekernel - a platform for running games
// gamekernel is (C) Copyright 2001-2002 by Kevin Meinert, Ben Scott
//
// Authors: Kevin Meinert <kevin@vrsource.org>
//          Ben Scott <bscott@iastate.edu>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the
// Free Software Foundation, Inc., 59 Temple Place - Suite 330,
// Boston, MA 02111-1307, USA.
//
// -----------------------------------------------------------------
// File:          $RCSfile: ContextData.h,v $
// Date modified: $Date: 2002-02-06 22:47:05 $
// Version:       $Revision: 1.6 $
// -----------------------------------------------------------------
//
////////////////// <GK heading END do not edit this line> ///////////////////
#ifndef CONTEXT_DATA_H
#define CONTEXT_DATA_H

#include "gk/gkCommon.h"
#include <vector>

GK_BEGIN_NAMESPACE

//-----------------------------------------------------------------------
//: map: int --> <Type>
//  Lets you associate data of any type to an integer "context"
//
// Ex: Map a float
//   ContextData<float> myData;
//   myData( 0 ) = 3.14596f;
//   myData( 1 ) = 6.29082f;
//   for (int context = 0; context < 2; ++context)
//   {
//      cout << "Data in context " << context << " is: " << myData( context ) << "\n";
//   }
//
// Output:
//   Data in context 0 is: 3.14596f
//	 Data in context 1 is: 6.29082f
//
//! NOTE: Requires that the type of the context data provide a default
//+  constructor used to initialize all of the copies of the data.
//-----------------------------------------------------------------------
template< class ContextDataType >
class ContextData
{
// client interface
public:
	//: Returns reference to user data for the contextId
    ContextDataType& operator() ( const int& contextId );

protected:
    //: Return a ptr to the correct data element in the current context
    //! PRE: We are in the draw function
    ContextDataType&  getItem( const int& contextId );

private:
	//: Vector of user data
    std::vector< ContextDataType >    _contextDataVector;
};

//: Return a ptr to the correct data element in the current context
//! PRE: We are in the draw function
template<class ContextDataType>
inline ContextDataType& ContextData<ContextDataType>::getItem( const int& contextId )
{
    // Make sure that we will reference a valid element
    while(_contextDataVector.size() <= contextId)
    {
		_contextDataVector.push_back(ContextDataType());
    }

    return _contextDataVector[contextId];
}

//: Returns reference to user data for the contextId
template<class ContextDataType>
inline ContextDataType& ContextData<ContextDataType>::operator() ( const int& contextId )
{
    return this->getItem( contextId );
}

GK_END_NAMESPACE

#endif
