
//////////////////////////////////////////////////////////////////////////////
//
//                         -=     machine endianness     =-
//
// Description: "routines for supporting machines with different endianness"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: Endian.h,v $
//    $Date: 2002-01-17 00:04:58 $
//    $Revision: 1.1.1.1 $
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
#ifndef ENDIAN_FUNCS
#define ENDIAN_FUNCS

// confused about namespaces?
// to call these funcs, use pixmi::byteReverse() for example
namespace pixmi
{
   //: Swap the bytes in any data type.
   // Motorola and Intel store their bytes in reversed formats <BR>
   // ex: An SGI image is native to the SGI system,            <BR>
   // to be read on an intel machine, it's bytes need to be reversed <BR>
   // NOTE: chars aren't affected by this since it only        <BR>
   // affects the order of bytes, not bits.
   template< class Type >
   inline void  byteReverse(Type& bytes)
   {       
       const int size = sizeof(Type);
       Type buf = 0;
       int x, y;

       //we want to index the bytes in the buffer
       unsigned char* buffer = (unsigned char*) &buf;

       for ( x = 0, y = size-1; 
                  x < size;
                  ++x, --y )
       {
         buffer[x] |= ((unsigned char*)&bytes)[y];
       }
       bytes = buf;
   }

   //: check the system for endianess
   inline bool isLittleEndian() 
   {
      union 
      {
         short   val;
         char    ch[sizeof(short)];
      } un;

      // initialize the memory that we'll probe
      un.val = 256;       // 0x10

      // If the 1 byte is in the low-order position (un.ch[1]), this is a
      // little-endian system.  Otherwise, it is a big-endian system.
      return un.ch[1] == 1;
   }

   //: check the system for endianess
   inline bool isBigEndian()
   {
      return !isLittleEndian();
   }   
};

#endif
