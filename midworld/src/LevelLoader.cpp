/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************* midworld-cpr beg
 *
 * midworld - retro post-nuclear mayhem
 * midworld is (C) Copyright 2002 by
 *    Chad Austin, Josh Brown, Johnathan Gurley,
 *    Kevin Meinert, Andres Reinot, Ben Scott
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
 * File:          $RCSfile: LevelLoader.cpp,v $
 * Date modified: $Date: 2002-12-03 06:50:44 $
 * Version:       $Revision: 1.6 $
 * -----------------------------------------------------------------
 *
 ********************************************************** midworld-cpr-end */
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <cppdom/cppdom.h>

#include "LevelLoader.h"
#include "GameState.h"
#include "EntityFactory.h"

#include "AmmoCrate.h"
#include "Enemy.h"
#include "Droid.h"
#include "GunPickup.h"
#include "NavNodeTree.h"
#include "StaticEntity.h"
#include "Turret.h"

using namespace cppdom;

namespace mw
{


   void 
   LevelLoader::handleStaticEntity(Entity* e, XMLNode &node)
   {
      XMLString name = node.getName();
      XMLString c_data;
      
      XMLNodePtr cNode = node.getChild(std::string("pos"));
      e->setPos(gmtl::Point3f(cNode->getAttribute(std::string("x")).getValue<float>(), 
                        cNode->getAttribute(std::string("y")).getValue<float>(),
                        cNode->getAttribute(std::string("z")).getValue<float>()));
      cNode = node.getChild(std::string("rot"));
      e->setRot(gmtl::Quatf(gmtl::makeRot<gmtl::Quatf>(gmtl::EulerAngleXYZf(
               gmtl::Math::deg2Rad(cNode->getAttribute("x").getValue<float>()),
               gmtl::Math::deg2Rad(cNode->getAttribute("y").getValue<float>()),
               gmtl::Math::deg2Rad(cNode->getAttribute("z").getValue<float>())))));
      cNode = node.getChild(std::string("model"));
      XMLNodePtr n = *(cNode->getChildren().begin());
      e->setModel(n->getCdata());
   }
   
   Entity*
   LevelLoader::handleTurretEntity(XMLNode &node, GameState* g)
   {
      Entity* t;
      XMLString name = node.getName();
      XMLString c_data;
      std::string nam, parent;
      int maxChildren, level;
      XMLNodePtr cNode= node.getChild(std::string("name"));
      XMLNodePtr n = *(cNode->getChildren().begin());
      nam = n->getCdata();
      cNode= node.getChild(std::string("parent"));
      n = *(cNode->getChildren().begin());
      parent = n->getCdata();
      cNode= node.getChild(std::string("maxChildren"));
      maxChildren = cNode->getAttribute(std::string("num")).getValue<int>();
      cNode= node.getChild(std::string("level"));
      level = cNode->getAttribute(std::string("nu")).getValue<int>();
      t = g->setupTurret(nam, parent, maxChildren, level);
      cNode = node.getChild(std::string("pos"));
      t->setPos(gmtl::Point3f(cNode->getAttribute(std::string("x")).getValue<float>(), 
                        cNode->getAttribute(std::string("y")).getValue<float>(),
                        cNode->getAttribute(std::string("z")).getValue<float>()));
      cNode = node.getChild(std::string("rot"));
      t->setRot(gmtl::Quatf(gmtl::makeRot<gmtl::Quatf>(gmtl::EulerAngleXYZf(
               gmtl::Math::deg2Rad(cNode->getAttribute("x").getValue<float>()),
               gmtl::Math::deg2Rad(cNode->getAttribute("y").getValue<float>()),
               gmtl::Math::deg2Rad(cNode->getAttribute("z").getValue<float>())))));
      cNode = node.getChild(std::string("model"));
      n = *(cNode->getChildren().begin());
      t->setModel(n->getCdata());
      return t;
   }


   Entity*
   LevelLoader::handleDroidEntity(XMLNode &node, GameState* g)
   {
      Entity* t;
      XMLString name = node.getName();
      XMLString c_data;
      std::string nam, parent;
      int maxChildren, level;
      XMLNodePtr cNode= node.getChild(std::string("name"));
      XMLNodePtr n = *(cNode->getChildren().begin());
      nam = n->getCdata();
      cNode= node.getChild(std::string("parent"));
      n = *(cNode->getChildren().begin());
      parent = n->getCdata();
      cNode= node.getChild(std::string("maxChildren"));
      maxChildren = cNode->getAttribute(std::string("num")).getValue<int>();
      cNode= node.getChild(std::string("level"));
      level = cNode->getAttribute(std::string("nu")).getValue<int>();
      t = g->setupTurret(nam, parent, maxChildren, level);
      cNode = node.getChild(std::string("pos"));
      t->setPos(gmtl::Point3f(cNode->getAttribute(std::string("x")).getValue<float>(), 
                        cNode->getAttribute(std::string("y")).getValue<float>(),
                        cNode->getAttribute(std::string("z")).getValue<float>()));
      cNode = node.getChild(std::string("rot"));
      t->setRot(gmtl::Quatf(gmtl::makeRot<gmtl::Quatf>(gmtl::EulerAngleXYZf(
               gmtl::Math::deg2Rad(cNode->getAttribute("x").getValue<float>()),
               gmtl::Math::deg2Rad(cNode->getAttribute("y").getValue<float>()),
               gmtl::Math::deg2Rad(cNode->getAttribute("z").getValue<float>())))));
      cNode = node.getChild(std::string("model"));
      n = *(cNode->getChildren().begin());
      t->setModel(n->getCdata());
      return t;
   }

   
   void 
   LevelLoader::handleAmmoEntity(Entity* e, XMLNode &node)
   {
      XMLString name = node.getName();
      XMLString c_data;
      
      XMLNodePtr cNode = node.getChild(std::string("pos"));
      e->setPos(gmtl::Point3f(cNode->getAttribute(std::string("x")).getValue<float>(), 
                        cNode->getAttribute(std::string("y")).getValue<float>(),
                        cNode->getAttribute(std::string("z")).getValue<float>()));
      cNode = node.getChild(std::string("rot"));
      e->setRot(gmtl::Quatf(gmtl::makeRot<gmtl::Quatf>(gmtl::EulerAngleXYZf(
               gmtl::Math::deg2Rad(cNode->getAttribute("x").getValue<float>()),
               gmtl::Math::deg2Rad(cNode->getAttribute("y").getValue<float>()),
               gmtl::Math::deg2Rad(cNode->getAttribute("z").getValue<float>())))));
      cNode = node.getChild(std::string("model"));
      XMLNodePtr n = *(cNode->getChildren().begin());
      e->setModel(n->getCdata());
   }
   
   Entity*
   LevelLoader::handleGunEntity(XMLNode &node, GameState* g)
   {
      Entity* t;
      XMLString name = node.getName();
      XMLString c_data;
      std::string type;
      XMLNodePtr cNode= node.getChild(std::string("type"));
      XMLNodePtr n = *(cNode->getChildren().begin());
      type = n->getCdata();
      t = EntityFactory::instance().create<GunPickup>(type);
      cNode = node.getChild(std::string("pos"));
      t->setPos(gmtl::Point3f(cNode->getAttribute(std::string("x")).getValue<float>(), 
                        cNode->getAttribute(std::string("y")).getValue<float>(),
                        cNode->getAttribute(std::string("z")).getValue<float>()));
      cNode = node.getChild(std::string("rot"));
      t->setRot(gmtl::Quatf(gmtl::makeRot<gmtl::Quatf>(gmtl::EulerAngleXYZf(
               gmtl::Math::deg2Rad(cNode->getAttribute("x").getValue<float>()),
               gmtl::Math::deg2Rad(cNode->getAttribute("y").getValue<float>()),
               gmtl::Math::deg2Rad(cNode->getAttribute("z").getValue<float>())))));
      cNode = node.getChild(std::string("model"));
      n = *(cNode->getChildren().begin());
      t->setModel(n->getCdata());
      return t;
   }

   

   void
   LevelLoader::dumpNode(XMLNode &node, GameState* g, int level)
   {
      XMLString name = node.getName();
      XMLNodeType type = node.getType();
      XMLString c_data;

      for(int i=0;i<level;i++) std::cout << " ";

      char c = ' ';
      switch(type)
      {
      case xml_nt_node:
         if(name.c_str() == std::string("static")){
            Entity* e;
            e = EntityFactory::instance().create<StaticEntity>();
            handleStaticEntity(e, node);
            g->add(e);
         }else if(name.c_str() == std::string("turret")){
            Entity* e;
            e = handleTurretEntity(node, g);
            g->add(e);
         }else if(name.c_str() == std::string("ammo")){
            Entity* e;
            e = EntityFactory::instance().create<AmmoCrate>();
            handleAmmoEntity(e, node);
            g->add(e);
         }else if(name.c_str() == std::string("gun")){
            Entity* e;
            e = handleGunEntity(node, g);
            g->add(e);
         }else if(name.c_str() == std::string("droid")){
            Entity* e;
            e = handleDroidEntity(node, g);
            g->add(e);
         }
            
         break;
      case xml_nt_leaf:
         c = '-';
         break;
      case xml_nt_document:
         c = '\\';
         break;
      case xml_nt_cdata:
         c = '#';
         c_data = node.getCdata();
         break;
      }

      if(type == xml_nt_cdata)
         std::cout << c << name.c_str() << "[" << c_data << "]" << std::endl;
      else
         std::cout << c << name.c_str() << std::endl;

      XMLAttributes attr = node.getAttrMap();

      // guru: added output of attributes
      for (XMLAttributes::iterator j = attr.begin(); j!=attr.end(); j++)
      {
         for (int i=0; i<level; i++)
            std::cout << " ";
         std::cout << "   ";
         std::cout << j->first << ": " << j->second << std::endl;
      }

      XMLNodeList& nlist = node.getChildren();

      XMLNodeList::const_iterator iter, stop;
      iter = nlist.begin();
      stop = nlist.end();

      while (iter != stop)
      {
         XMLNodePtr node = *iter;

         dumpNode ( *node, g, level+1 );

         ++iter;
      }
   }

   void 
   LevelLoader::process_xml( std::string filename, GameState* g)
   {
      std::cout << "processing [" << filename << "] ..." << std::endl;

      XMLContextPtr context( new XMLContext );
      XMLDocument node( context );
      std::ifstream istr( filename.c_str() );

      // Verify that file opened
      if(!istr)
      {
         std::cerr << "Bad file: " << filename << std::endl;
         return;
      }

      try
      {
   //      clock_t tstart = ::clock();

         node.load( istr, context );

   //      clock_t tstop = ::clock();
   //      cout << " needed " <<
   //         (tstop-tstart)/static_cast<float>(CLOCKS_PER_SEC)
   //         << " seconds." << endl;

         dumpNode( node, g );

         std::ofstream ostr( "parsetest.xml" );
         node.save( ostr );
         ostr.close();

      }
      catch (XMLError e)
      {
         XMLLocation where( context->getLocation() );
         XMLString errmsg;
         e.getStrError(errmsg);

         // print out where the error occured
         std::cout << filename << ":" << where.getLine() << " ";
         std::cout << "at position " << where.getPos();
         std::cout << ": error: " << errmsg.c_str();
         std::cout << std::endl;

         // print out line where the error occured
         std::ifstream errfile( filename.c_str() );
         if(!errfile)
         {
            std::cerr << "Can't open file [" << filename << "] to output error" << std::endl;
         }

         int linenr = where.getLine();
         char linebuffer[1024];
         for(int i=0; i<linenr && !errfile.eof(); i++)
            errfile.getline( linebuffer,1024 );

         int pos = where.getPos();
         if (pos>=80)
            pos %= 80;

         std::string err_line( linebuffer + (where.getPos()-pos) );
         if (err_line.length()>=79)
            err_line.erase(79);
         std::cout << err_line << std::flush;
         std::cout << err_line.c_str() << std::endl;
         std::cout << linebuffer << std::endl;
         for(int j=2;j<pos;j++)
            std::cout << " ";
      std::cout << '^' << std::endl;
   
      }
   }


}  
      

   

