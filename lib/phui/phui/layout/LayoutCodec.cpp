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
 * File:          $RCSfile: LayoutCodec.cpp,v $
 * Date modified: $Date: 2003-01-05 02:19:17 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ************************************************************** phui-cpr-end */
#include <iostream>
#include <cppdom/cppdom.h>
#include "LayoutCodec.h"
#include "../Window.h"
#include "../Button.h"

namespace phui
{
   WidgetPtr processNode(cppdom::XMLNodePtr node);

   WidgetPtr
   processPhuiNode(cppdom::XMLNodePtr node)
   {
      return processNode(node->getChild("window"));
//      cppdom::XMLNodeList children = node->getChildren();
//      cppdom::XMLNodeListIterator itr = children.begin();
//      while (itr != children.end()) {
//         ++itr;
//      }
   }

   Point
   processPositionNode(cppdom::XMLNodePtr node)
   {
      return Point(node->getAttribute("x").getValue<int>(),
                   node->getAttribute("y").getValue<int>());
   }

   Size
   processSizeNode(cppdom::XMLNodePtr node)
   {
      return Size(node->getAttribute("width").getValue<int>(),
                  node->getAttribute("height").getValue<int>());
   }

   WidgetPtr
   processWindowNode(cppdom::XMLNodePtr node)
   {
      WindowPtr wnd;
      if (node->hasAttribute("text"))
      {
         wnd = Window::create(node->getAttribute("text").getValue<std::string>());
      }
      else
      {
         wnd = Window::create();
      }

      if (node->hasAttribute("visible"))
      {
         wnd->setVisible(node->getAttribute("visible").getValue<bool>());
      }

      cppdom::XMLNodeList children = node->getChildren();
      cppdom::XMLNodeListIterator itr = children.begin();
      while (itr != children.end())
      {
         cppdom::XMLNodePtr child = *itr;

         // Handle a position node
         if (child->getName() == "position")
         {
            wnd->setPosition(processPositionNode(child));
         }
         // Handle size node
         else if (child->getName() == "size")
         {
            wnd->setSize(processSizeNode(child));
         }
         // Handle subchild node
         else
         {
            wnd->add(processNode(child));
         }
         ++itr;
      }

      return wnd;
   }

   WidgetPtr
   processButtonNode(cppdom::XMLNodePtr node)
   {
      ButtonPtr btn = Button::create();
      if (node->hasAttribute("text"))
      {
         btn->setText(node->getAttribute("text").getValue<std::string>());
      }

      cppdom::XMLNodeList children = node->getChildren();
      cppdom::XMLNodeListIterator itr = children.begin();
      while (itr != children.end())
      {
         cppdom::XMLNodePtr child = *itr;

         // Handle a position node
         if (child->getName() == "position")
         {
            btn->setPosition(processPositionNode(child));
         }
         // Handle size node
         else if (child->getName() == "size")
         {
            btn->setSize(processSizeNode(child));
         }
         // Handle subchild node
         else
         {
            std::cerr << "Unknown node: " << child->getName() << std::endl;
         }
         ++itr;
      }

      return btn;
   }

   WidgetPtr
   processNode(cppdom::XMLNodePtr node)
   {
      if (node->getName() == "phui")
      {
         return processPhuiNode(node);
      }
      else if (node->getName() == "window") 
      {
         return processWindowNode(node);
      }
      else if (node->getName() == "button") 
      {
         return processButtonNode(node);
      }
      else
      {
         std::cerr << "Unknown node: " << node->getName() << std::endl;
         WidgetPtr null;
         return null;
      }
   }

   WidgetPtr
   LayoutCodec::decode(const std::string& file)
   {
      cppdom::XMLContextPtr ctx(new cppdom::XMLContext);
      cppdom::XMLDocument doc(ctx);

      // Load the XML document from a file
      try
      {
         doc.loadFile(file);
      }
      catch (cppdom::XMLError& e)
      {
         std::cerr << "Errpr: " << e.getString() << std::endl;
         if (e.getInfo().size())
         {
            std::cerr << "File: " << e.getInfo() << std::endl;
         }
         WidgetPtr null;
         return null;
      }

      std::cout << "Loading layout: " << file << std::endl;
      return processNode(doc.getChild("phui"));

      WidgetPtr null;
      return null;
   }
}
