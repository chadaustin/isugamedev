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
 * File:          $RCSfile: PyWidget.cpp,v $
 * Date modified: $Date: 2005-01-25 01:42:41 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include <boost/python.hpp>
#include "../phui.h"

using namespace boost::python;
using namespace phui;

void makeWidget()
{
   // Widget
   class_<Widget, WidgetPtr, boost::noncopyable>("Widget", no_init)
      .def("draw", &Widget::draw)
      .def("show", &Widget::show)
      .def("hide", &Widget::hide)
      .def("contains", &Widget::contains)
      .def("getScreenPosition", &Widget::getScreenPosition)
      .def("hasFocus", &Widget::hasFocus)
      .add_property("position", make_function(&Widget::getPosition, return_internal_reference<>()),
                                make_function(&Widget::setPosition))
      .add_property("size", make_function(&Widget::getSize, return_internal_reference<>()),
                            make_function(&Widget::setSize))
      .add_property("enabled", &Widget::isEnabled, &Widget::setEnabled)
      .add_property("visible", &Widget::isVisible, &Widget::setVisible)
      .add_property("backgroundColor", make_function(&Widget::getBackgroundColor, return_internal_reference<>()),
                                       make_function(&Widget::setBackgroundColor))
      .add_property("foregroundColor", make_function(&Widget::getForegroundColor, return_internal_reference<>()),
                                       make_function(&Widget::setForegroundColor))
//         .add_property("font", make_function(&Widget::getFont, return_internal_reference<>()),
//                               make_function(&Widget::setFont))
      .add_property("parent", &Widget::getParent)
   ;
}
