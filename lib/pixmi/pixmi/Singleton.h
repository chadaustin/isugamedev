
//////////////////////////////////////////////////////////////////
//
//                         -=     Singleton     =-
//
// Definition: "restrict access to a class to one instance only."
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: Singleton.h,v $
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
#ifndef _SINGLETON_H_
#define _SINGLETON_H_

namespace pixmi
{
   // you can use this coolio class to make a singleton,
   // just inherit like so...
   //
   // class myClass : public pixmi::Singleton<myClass>
   //
   template< class singleClass >
   class Singleton
   {
   public:
      // access your class with myClass::instance().
      inline static singleClass& instance( void )        
      {    
                                                      
         static singleClass* the_instance1 = NULL;   

         if (the_instance1 == NULL)
         {                                            
            if (the_instance1 == NULL)        
            { the_instance1 = new singleClass; }
         }                                      
         return *the_instance1;    
         
         //static singleClass the_instance1;
         //return the_instance1;
      }

   protected:
      // dont create a singleton with new!  
      // use instance()
      Singleton()
      {
      }

      // don't delete a singleton!
      virtual ~Singleton()
      {
      }
   };
}; // end of namespace kev

#endif
