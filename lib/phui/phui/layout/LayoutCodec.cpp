/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/**************************************************************** phui-head beg
 *
 * phui - flexible user interface subsystem
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Josh Carlson <josh@chegg.com>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: LayoutCodec.cpp,v $
 * Date modified: $Date: 2002-12-23 12:56:50 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************* phui-head-end */
/***************************************************************** phui-cpr beg
 *
 * phui - flexible user interface subsystem
 * phui is (C) Copyright 2002 by Chad Austin, Josh Carlson, Ben Scott
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
 ************************************************************** phui-cpr-end */
#include <iostream>
#include <cppdom/cppdom.h>
#include "LayoutCodec.h"
#include "../Window.h"
#include "../Button.h"

namespace phui
{
   Widget* processNode(cppdom::XMLNodePtr node);

   Widget*
   processPhuiNode(cppdom::XMLNodePtr node) {
      return processNode(node->getChild("window"));
//      cppdom::XMLNodeList children = node->getChildren();
//      cppdom::XMLNodeListIterator itr = children.begin();
//      while (itr != children.end()) {
//         ++itr;
//      }
   }

   Point
   processPositionNode(cppdom::XMLNodePtr node) {
      return Point(node->getAttribute("x").getValue<int>(),
                   node->getAttribute("y").getValue<int>());
   }

   Size
   processSizeNode(cppdom::XMLNodePtr node) {
      return Size(node->getAttribute("width").getValue<int>(),
                  node->getAttribute("height").getValue<int>());
   }

   Widget*
   processWindowNode(cppdom::XMLNodePtr node) {
      Window* wnd = 0;
      if (node->hasAttribute("text")) {
         wnd = new Window(node->getAttribute("text").getValue<std::string>());
      } else {
         wnd = new Window();
      }

      if (node->hasAttribute("visible")) {
         wnd->setVisible(node->getAttribute("visible").getValue<bool>());
      }

      cppdom::XMLNodeList children = node->getChildren();
      cppdom::XMLNodeListIterator itr = children.begin();
      while (itr != children.end()) {
         cppdom::XMLNodePtr child = *itr;

         // Handle a position node
         if (child->getName() == "position") {
            wnd->setPosition(processPositionNode(child));
         }
         // Handle size node
         else if (child->getName() == "size") {
            wnd->setSize(processSizeNode(child));
         }
         // Handle subchild node
         else {
            wnd->add(processNode(child));
         }
         ++itr;
      }

      return wnd;
   }

   Widget*
   processButtonNode(cppdom::XMLNodePtr node) {
      Button* btn = new Button();
      if (node->hasAttribute("text")) {
         btn->setText(node->getAttribute("text").getValue<std::string>());
      }

      cppdom::XMLNodeList children = node->getChildren();
      cppdom::XMLNodeListIterator itr = children.begin();
      while (itr != children.end()) {
         cppdom::XMLNodePtr child = *itr;

         // Handle a position node
         if (child->getName() == "position") {
            btn->setPosition(processPositionNode(child));
         }
         // Handle size node
         else if (child->getName() == "size") {
            btn->setSize(processSizeNode(child));
         }
         // Handle subchild node
         else {
            std::cerr << "Unknown node: " << child->getName() << std::endl;
         }
         ++itr;
      }

      return btn;
   }

   Widget*
   processNode(cppdom::XMLNodePtr node) {
      if (node->getName() == "phui") {
         return processPhuiNode(node);
      }
      else if (node->getName() == "window") {
         return processWindowNode(node);
      }
      else if (node->getName() == "button") {
         return processButtonNode(node);
      }
      else {
         std::cerr << "Unknown node: " << node->getName() << std::endl;
         return 0;
      }
   }

   Widget*
   LayoutCodec::decode(const std::string& file) {
      cppdom::XMLContextPtr ctx(new cppdom::XMLContext);
      cppdom::XMLDocument doc(ctx);

      // Load the XML document from a file
      try {
         doc.loadFile(file);
      }
      catch (cppdom::XMLError& e) {
         std::cerr << "Errpr: " << e.getString() << std::endl;
         if (e.getInfo().size()) {
            std::cerr << "File: " << e.getInfo() << std::endl;
         }
         return 0;
      }

      std::cout << "Loading layout: " << file << std::endl;
      return processNode(doc.getChild("phui"));

      return 0;
   }
}
