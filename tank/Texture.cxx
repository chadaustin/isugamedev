
//////////////////////////////////////////////////////////////////
//
//                         -=     Texture     =-
//
// Definition: "Texture class."
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: Texture.cxx,v $
//    $Date: 2001-09-10 15:27:29 $
//    $Revision: 1.1 $
//    Copyright (C) 1998, 1999, 2000  Kevin Meinert, kevin@vrsource.org
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
#include <iostream>
#include "Texture.h" // My Header

//	Constructor.
Texture::Texture() : mImage( NULL ), model( MODULATE ), 
		    wrapS( REPEAT ), wrapT( REPEAT ), 
		    filtering( NEAREST )
{
   this->setResourceID();
}

Texture::Texture( const Texture &texture ) : model( MODULATE ), 
		    wrapS( REPEAT ), wrapT( REPEAT ), 
		    filtering( NEAREST ), mImage(NULL)
{
    // reference the image.
    this->setImage( texture.mImage );
	
    wrapS   = texture.wrapS; //repeat,clamp
    wrapT   = texture.wrapT; //repeat,clamp
    model   = texture.model; //blend,modulate,decal
    filtering = texture.filtering;
    resourceId = texture.resourceId;
    
//    std::cout<<"copy texture: "<<(int)this<<" has id of: "<<resourceId.id<<" "<<resourceId.valid<<"\n"<<std::flush;
}

void Texture::setResourceID()
{
   static unsigned int _rid = 0;
   ++_rid;
   resourceId.id = _rid;
   resourceId.valid = true;
   
//   std::cout<<"texture: "<<(int)this<<" has id of: "<<resourceId.id<<" "<<resourceId.valid<<"\n"<<std::flush;
}
