
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     ContextData.h     =-
//
//  Define.h: a class to map data to contexts
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: ContextData.h,v $
//    $Date: 2002-01-30 06:18:27 $
//    $Revision: 1.2 $
//    Copyright (C) 1998, 1999, 2000  Kevin Meinert, KevinMeinert@bigfoot.com
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Library General Public
//    License as published by the Free Software Foundation; either
//    version 2 of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Library General Public License for more details.
//
//    You should have received a copy of the GNU Library General Public
//    License along with this library; if not, write to the Free
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
///////////////// <auto-copyright END do not edit this line> ///////////////////

//////////////////////////////////////////////////////////////////////////////
#ifndef CONTEXT_DATA_H
#define CONTEXT_DATA_H


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
#include <vector>
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

#endif
