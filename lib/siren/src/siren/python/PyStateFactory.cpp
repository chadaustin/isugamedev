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
 * File:          $RCSfile: PyStateFactory.cpp,v $
 * Date modified: $Date: 2003-02-14 05:41:34 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#include <boost/python.hpp>
#include <siren/siren.h>

using namespace boost::python;
using namespace siren;

class StateCreatorWrap : public StateCreator
{
public:
   StateCreatorWrap(PyObject* self)
      : mSelf(self)
   {}

   StatePtr create()
   {
      return call_method<StatePtr>(mSelf, "create");
   }

private:
   PyObject* mSelf;
};

void exportStateFactory()
{
   // StateCreator
   class_<StateCreator, bases<>, StateCreatorWrap, boost::noncopyable>("StateCreator")
      .def("create", &StateCreatorWrap::create)
   ;

   // StateFactory
   class_<StateFactory, bases<>, boost::noncopyable>("StateFactory", no_init)
      .def("create", &StateFactory::create)
      .def("register", &StateFactory::registerCreator, with_custodian_and_ward<1,2>())
   ;

   /**
    * Define the StateFactory singleton accessor. Since python is so cool, we
    * will overwrite the StateFactory symbol with this function that will return
    * the StateFactory singleton class so that it looks like any normal class.
    */
   def("StateFactory", &StateFactory::getInstance, return_value_policy<reference_existing_object>());
}
