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
 * Date modified: $Date: 2003-01-08 09:10:12 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include <boost/python.hpp>
#include "../Utility.h"

using namespace boost::python;

extern void makeActionEvent();
extern void makeActionListener();
extern void makeButton();
extern void makeCheckBox();
extern void makeColor();
extern void makeInsets();
extern void makeLabel();
extern void makeLayoutConstraint();
extern void makeListBox();
extern void makePoint();
extern void makeRootWidget();
extern void makeSize();
extern void makeTextField();
extern void makeWidget();
extern void makeWidgetContainer();
extern void makeWindow();
extern void makeWindowAdapter();
extern void makeWindowEvent();
extern void makeWindowListener();


BOOST_PYTHON_MODULE(phui)
{
   makeColor();
   makeInsets();
   makePoint();
   makeSize();

   makeActionEvent();
   makeActionListener();
   makeWindowEvent();
   makeWindowListener();
//   makeWindowAdapter();

   makeLayoutConstraint();

   makeWidget();
   makeWidgetContainer();

   makeButton();
   makeCheckBox();
   makeLabel();
   makeListBox();
   makeRootWidget();
   makeTextField();
   makeWindow();
}
