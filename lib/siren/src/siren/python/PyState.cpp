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
 * File:          $RCSfile: PyState.cpp,v $
 * Date modified: $Date: 2003-02-14 05:41:34 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************* siren-cpr-end */
#include <boost/python.hpp>
#include <siren/siren.h>

using namespace boost::python;
using namespace siren;

class StateWrap : public State
{
public:
   StateWrap(PyObject* self)
      : mSelf(self)
   {}

   void update(float dt)
   {
      call_method<void>(mSelf, "update", dt);
   }

   void draw() const
   {
      call_method<void>(mSelf, "draw");
   }

private:
   PyObject* mSelf;
};

void exportState()
{
   // State
   class_<State, bases<>, StateWrap, boost::noncopyable>("State")
      .def("update", &StateWrap::update)
      .def("draw", &StateWrap::draw)
      .def("quit", &StateWrap::quit)
   ;
}
