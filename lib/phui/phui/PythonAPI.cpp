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
 * File:          $RCSfile: PythonAPI.cpp,v $
 * Date modified: $Date: 2003-01-06 03:30:00 $
 * Version:       $Revision: 1.5 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include <boost/python.hpp>
#include "phui.h"

using namespace boost::python;

namespace phui
{
   namespace python
   {
//      struct PyWidget : public Widget
//      {
//         PyWidget(PyObject* self)
//            : mSelf(self)
//         {}
//
//         void draw() { return call_method<void>(mSelf, "draw"); }
//
//         PyObject* mSelf;
//      };

      struct PyLayoutConstraint : public LayoutConstraint
      {
         PyLayoutConstraint(PyObject* self)
            : mSelf(self)
         {}

         const std::string getType() { return call_method<std::string>(mSelf, "getType"); }

         PyObject* mSelf;
      };

      ButtonPtr createButton()
      {
         return Button::create();
      }

      WindowPtr createWindow()
      {
         return Window::create();
      }
   }

   using namespace python;
   BOOST_PYTHON_MODULE(phui)
   {
      // Tell Boost.Python that it can convert between appropriate shared_ptr types
      implicitly_convertible<ButtonPtr, WidgetPtr>();
      implicitly_convertible<WidgetContainerPtr, WidgetPtr>();
      implicitly_convertible<RootWidgetPtr, WidgetContainerPtr>();
      implicitly_convertible<WindowPtr, WidgetContainerPtr>();

      // Point
      class_<Point>("Point")
         .def(init<int, int>())
         .def(init<Point>())
         .def("set", &Point::set)
         .def(self + self)
         .def(self - self)
         .def(self += self)
         .def(self -= self)
         .def(self == self)
         .def(self != self)
//         .def(str(self))
         .def_readwrite("x", &Point::x)
         .def_readwrite("y", &Point::y)
      ;

      // Size
      class_<Size>("Size")
         .def(init<int, int>())
         .def(init<Size>())
         .def("set", &Size::set)
         .def(self == self)
         .def(self != self)
//         .def(str(self))
         .add_property("width", &Size::getWidth, &Size::setWidth)
         .add_property("height", &Size::getHeight, &Size::setHeight)
      ;

      // Color
      class_<Colorf>("Color")
         .def(init<float, float, float, float>())
         .def(init<Colorf>())
         .def("set", &Colorf::set)
         .def(self == self)
         .def(self != self)
//         .def(str(self))
         .def_readwrite("r", &Colorf::r)
         .def_readwrite("g", &Colorf::g)
         .def_readwrite("b", &Colorf::b)
         .def_readwrite("a", &Colorf::a)
      ;

      // Insets
      class_<Insets>("Insets")
         .def(init<int, int, int, int>())
         .def(init<Insets>())
         .def("set", &Point::set)
         .def(self == self)
         .def(self != self)
//         .def(str(self))
         .add_property("left", &Insets::getLeft, &Insets::setLeft)
         .add_property("right", &Insets::getRight, &Insets::setRight)
         .add_property("top", &Insets::getTop, &Insets::setTop)
         .add_property("bottom", &Insets::getBottom, &Insets::setBottom)
      ;

      // LayoutContraint
      class_<LayoutConstraint, PyLayoutConstraint, boost::noncopyable>("LayoutConstraint", no_init)
         .def("type", &PyLayoutConstraint::getType)
      ;

      // LayoutManager
      class_<LayoutManager, LayoutManagerPtr>("LayoutManager", init<WidgetContainer*, LayoutConstraintPtr>())
         .def("add", &LayoutManager::add)
         .def("remove", &LayoutManager::remove)
         .def("resize", &LayoutManager::resize)
         .add_property("valid", &LayoutManager::isValid)
      ;

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

      // WidgetContainer
      class_<WidgetContainer, bases<Widget>, WidgetContainerPtr, boost::noncopyable>("WidgetContainer", no_init)
         .def("add", &WidgetContainer::add)
         .def("remove", &WidgetContainer::remove)
         .def("getWidget", &WidgetContainer::getWidget)
         .def("draw", &WidgetContainer::draw)
         .def("setLayoutManager", &WidgetContainer::setLayoutManager)
         .add_property("numChildren", &WidgetContainer::getNumChildren)
      ;

      // Button
      class_<Button, bases<Widget>, ButtonPtr>("Button", no_init)
         .def("addActionListener", &Button::addActionListener)
         .def("removeActionListener", &Button::removeActionListener)
         .def("draw", &Button::draw)
         .add_property("text", make_function(&Button::getText, return_internal_reference<>()),
                               make_function(&Button::setText))
      ;

      // RootWidget
      class_<RootWidget, bases<WidgetContainer>, RootWidgetPtr>("RootWidget", no_init)
      ;

      // Window
      class_<Window, bases<WidgetContainer>, WindowPtr>("Window", no_init)
         .def("addWindowListener", &Window::addWindowListener)
         .def("removeWindowListener", &Window::removeWindowListener)
      ;

      def("createRoot", CreateRoot);
      def("createButton", createButton);
      def("createWindow", createWindow);

   }
}
