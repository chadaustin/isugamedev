/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/***************************************************************** phui-cpr beg
 *
 * phui - flexible user interface subsystem
 * phui is (C) Copyright 2002 by
 *      Chad Austin, Josh Carlson, Johnathan Gurley,
 *      Ben Scott, Levi Van Oort
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
 * File:          $RCSfile: PyButton.cpp,v $
 * Date modified: $Date: 2005-01-25 17:29:03 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include <boost/python.hpp>
#include "../phui.h"

using namespace boost::python;
using namespace phui;

ButtonPtr createButton()
{
   return Button::create();
}

void makeButton()
{
   // Button
   class_<Button, bases<Widget>, ButtonPtr>("Button", no_init)
      .def("addActionListener", &Button::addActionListener)
      .def("removeActionListener", &Button::removeActionListener)
      .add_property("text", make_function(&Button::getText, return_internal_reference<>()),
                            make_function(&Button::setText))
   ;

   def("createButton", createButton);
}
