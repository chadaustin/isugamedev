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
 * Date modified: $Date: 2003-01-06 13:41:56 $
 * Version:       $Revision: 1.10 $
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
      struct LayoutConstraintWrap : public LayoutConstraint
      {
         LayoutConstraintWrap(PyObject* self)
            : mSelf(self)
         {}

         const std::string getType() { return call_method<std::string>(mSelf, "getType"); }

         PyObject* mSelf;
      };
      typedef boost::shared_ptr<LayoutConstraintWrap> LayoutConstraintWrapPtr;

      struct ActionListenerWrap : public ActionListener
      {
         ActionListenerWrap(PyObject* self)
            : mSelf(self)
         {}

         void onAction(const ActionEvent& evt) { return call_method<void>(mSelf, "onAction"); }

         PyObject* mSelf;
      };
      typedef boost::shared_ptr<ActionListenerWrap> ActionListenerWrapPtr;

#define PHUI_CREATE(Type)           \
   Type ## Ptr create ## Type()     \
   {                                \
      return Type::create();        \
   }
   PHUI_CREATE(Button)
   PHUI_CREATE(CheckBox)
   PHUI_CREATE(Label)
   PHUI_CREATE(ListBox)
   PHUI_CREATE(Window)
   PHUI_CREATE(TextField)
#undef PHUI_CREATE
   }

   using namespace python;
   BOOST_PYTHON_MODULE(phui)
   {
      // Tell Boost.Python that it can convert between appropriate shared_ptr types
      implicitly_convertible<ButtonPtr, WidgetPtr>();
      implicitly_convertible<CheckBoxPtr, WidgetPtr>();
      implicitly_convertible<LabelPtr, WidgetPtr>();
      implicitly_convertible<ListBoxPtr, WidgetPtr>();
      implicitly_convertible<TextFieldPtr, WidgetPtr>();
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

      // ActionEvent
      class_<ActionEvent>("ActionEvent", init<WidgetPtr>())
         .add_property("source", &ActionEvent::getSource)
      ;

      // ActionListener
      class_<ActionListener, ActionListenerWrap, boost::noncopyable>("ActionListener")
         .def("onAction", &ActionListenerWrap::onAction)
      ;


      // LayoutContraint
//      class_<LayoutConstraint, LayoutConstraintWrap, boost::noncopyable>("LayoutConstraint", no_init)
//         .def("type", &LayoutConstraintWrap::getType)
//      ;

      // LayoutManager
//      class_<LayoutManager, LayoutManagerPtr>("LayoutManager",
//                                              init<WidgetContainer*,
//                                                   LayoutConstraintPtr>())
//         .def("add", &LayoutManager::add)
//         .def("remove", &LayoutManager::remove)
//         .def("resize", &LayoutManager::resize)
//         .add_property("valid", &LayoutManager::isValid)
//      ;

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
         .def("setLayoutManager", &WidgetContainer::setLayoutManager)
         .add_property("numChildren", &WidgetContainer::getNumChildren)
      ;

      // Button
      class_<Button, bases<Widget>, ButtonPtr>("Button", no_init)
         .def("addActionListener", &Button::addActionListener)
         .def("removeActionListener", &Button::removeActionListener)
         .add_property("text", make_function(&Button::getText, return_internal_reference<>()),
                               make_function(&Button::setText))
      ;

      // CheckBox
      class_<CheckBox, bases<Widget>, CheckBoxPtr>("CheckBox", no_init)
         .def("check", &CheckBox::check)
         .def("uncheck", &CheckBox::uncheck)
         .add_property("checked", &CheckBox::isChecked, &CheckBox::setChecked)
      ;

      // Label
      class_<Label, bases<Widget>, LabelPtr>("Label", no_init)
         .add_property("text", make_function(&Label::getText, return_internal_reference<>()),
                               make_function(&Label::setText))
      ;

      // ListBox
      class_<ListBox, bases<Widget>, ListBoxPtr>("ListBox", no_init)
         .def("add", &ListBox::add)
         .def("remove", &ListBox::remove)
         .def("clear", &ListBox::clear)
         .def("get", &ListBox::get, return_internal_reference<>())
         .def("getSelectedIndex", &ListBox::getSelectedIndex)
         .def("addListSelectionListener", &ListBox::addListSelectionListener)
         .def("removeListSelectionListener", &ListBox::removeListSelectionListener)
      ;

      // TextField
      class_<TextField, bases<Widget>, TextFieldPtr>("TextField", no_init)
         .add_property("text", make_function(&TextField::getText, return_internal_reference<>()),
                               make_function(&TextField::setText))
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
      def("createCheckBox", createCheckBox);
      def("createLabel", createLabel);
      def("createListBox", createListBox);
      def("createTextField", createTextField);
      def("createWindow", createWindow);
   }
}
