//////////////////////////////////////////////////////////////////
//
//                         -=   objimporter     =-
//
// Definition: "obj file loader"
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: ObjImporter.h,v $
//    $Date: 2001-09-30 23:28:37 $
//    $Revision: 1.11 $
//    Copyright (C) 1998, 1999, 2000  Kevin Meinert, kevin@vrsource.org
//
//    This library is free software; you can redistribute it and/or
//    modify it under the terms of the GNU Library General Public
//    License as published by the Free Software Foundation; either
//    version 2 of the License, or (at your option) any later version.
//
//    This library is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//    Library General Public License for more details.
//
//    You should have received a copy of the GNU Library General Public
//    License along with this library; if not, write to the Free
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
///////////////// <auto-copyright END do not edit this line> ///////////////////
#ifndef OBJ_IMPORTER_INCLUDED
#define OBJ_IMPORTER_INCLUDED

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <fstream>

#include "regexx/regexx.hh"
#include "CFileIO.h"

#include "Vertex.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "ImageManager.h"
#include "GState.h"

#include "GeoSet.h"

namespace kev
{
class ObjImporter
{
public:
   void loadMaterialLib( std::vector< safe_ptr<GState> >& matlist, const std::string& pathToFiles, const std::string& fileNameWithoutPath )
   {
      std::string filetext;
      //int num_of_matches = 0;

      std::string filename = pathToFiles + fileNameWithoutPath;


      std::cout<<"- Loading: "<<fileNameWithoutPath<<"\n"<<std::flush;
      bool exists = CFileIO::fileExists( filename.c_str() );
      if (exists == false)
      {
         std::cout<<"  - WARNING: File not found: \""<<filename.c_str()<<"\"\n"<<std::flush;
         return;
      }

      std::fstream dataFile;
      dataFile.open( filename.c_str(), std::ios::in );
      assert( dataFile.good() && "couldn't open .mtl file" );
      CFileIO::getAll( dataFile, filetext );
      dataFile.close();

      try 
      {
         std::vector< std::string > matStrings;
         std::string* strPtr = NULL;

         // parse line by line
         regexx::Regexx matchOneLine;
         int num_of_matches = matchOneLine.exec( filetext,"([^\n]*[\n])", regexx::Regexx::global);
         filetext = "";
         for (int lines = 0; lines < matchOneLine.match.size(); ++lines)
         {
            std::string oneLine = matchOneLine.match[lines].atom[0];
      
            regexx::Regexx removeComments;
            oneLine = removeComments.replace( oneLine, "#[^\n]*\n", "", regexx::Regexx::global | regexx::Regexx::newline);
         
            // for every "newmtl" tag, start a new string, this will effectively divide the file
            regexx::Regexx extractMaterial;
            num_of_matches = extractMaterial.exec( oneLine,"newmtl[ ]+(.*)", regexx::Regexx::global);
            if (num_of_matches)
            {
               matStrings.push_back( std::string("") );
               strPtr = &matStrings[ matStrings.size() - 1 ];
            }

            if (strPtr != NULL)
               *strPtr += oneLine;
         }

         
         // for each material found, extract the information...
         //std::cout<<matStrings.size()<<"\n"<<std::flush;
         for (int x = 0; x < matStrings.size(); ++x)
         {
            //std::cout<<matStrings[x]<<"\n"<<std::flush;
            // newmtl blue_material
            // Ka  0.08889 0.06405 0.18170
            // Kd  0.26667 0.19216 0.54510
            // Ks  0.90000 0.90000 0.90000
            // d  1.00000
            // Ns  0.50000
            // illum 2
            // map_Kd 64.tga
            GState* gstate = new GState;
            
            // get the material name
            regexx::Regexx extractMaterial;
            num_of_matches = extractMaterial.exec( matStrings[x],"newmtl[ ]+([^\n]*)", regexx::Regexx::global);
            if (num_of_matches)
            {
               gstate->setName( extractMaterial.match[0].atom[0].str() );
               //std::cout<<"new: \""<<gstate->name<<"\"\n"<<std::flush;
            }

            // get the material/color info
            regexx::Regexx extractInfo;
            num_of_matches = extractInfo.exec( matStrings[x], "(Ka|Kd|Ks)[ ]+([0-9.]*)[ ]+([0-9.]*)[ ]+([0-9.]*)", regexx::Regexx::global );
            if (num_of_matches)
            {
               for (int x = 0; x < num_of_matches; ++x)
               {
                  std::string matType = extractInfo.match[x].atom[0].str();
                  //int size = extractInfo.match.size();
                  //size = extractInfo.match[x].atom.size();
                  //std::string& temp = extractInfo.match[x].atom[1].str();
                  float r = atof( extractInfo.match[x].atom[1].str().c_str() );
                  float g = atof( extractInfo.match[x].atom[2].str().c_str() );
                  float b = atof( extractInfo.match[x].atom[3].str().c_str() );

                  if (matType == "Ka")
                     gstate->mat.setColor( Material::ambient, r, g, b );
                  else if (matType == "Kd")
                     gstate->mat.setColor( Material::diffuse, r, g, b );
                  else if (matType == "Ks")
                     gstate->mat.setColor( Material::specular, r, g, b );
               }
            }

            // get the image map info
            regexx::Regexx extractMap;
            num_of_matches = extractMap.exec( matStrings[x], "(map_Kd|map_Ka|map_Ks)[ ]+([^\n]*)", regexx::Regexx::global );
            if (num_of_matches)
            {
//             std::cout<<"map\n"<<std::flush;
               for (int x = 0; x < num_of_matches; ++x)
               {
                  gstate->mapName = pathToFiles + extractMap.match[x].atom[1].str();
                  std::cout<<"- Loading: \""<<gstate->mapName<<"\"\n"<<std::flush;
                  Image* image = new Image;
                  if (ImageManager::instance().load( gstate->mapName.c_str(), *image ) == false)
                  {
                     std::cout<<"   - \""<<gstate->mapName<<"\" not found.\n"<<std::flush;
                     delete image;
                  }
                  else
                  {
                     gstate->texture.setImage( image );
                  }                  
               }
            }
            //gstate->setName( filename );
            matlist.push_back( gstate );
         }
      }
      catch (regexx::Regexx::CompileException &e)
      {
         std::cerr << e.message() << std::endl;
      }
   }
   
   bool lookupGState( const std::string& name,
                      const std::vector< safe_ptr<GState> >& gstateList,
                      GState* &gstate )
         
   {
      //std::cout<<"searching for: \""<<name<<"\"\n"<<std::flush;
      for (int x = 0; x < gstateList.size(); ++x)
      {
         if (name == gstateList[x]->getName())
         {
            gstate = gstateList[x];
            //std::cout<<"found: \""<<gstate->getName()<<"\"\n"<<std::flush;
            return true;
         }
      }

      return false;
   }

   class Indicies
   {
   public:
         Indicies() : mat( NULL ) {}
      std::vector<unsigned int> cindex;
      std::vector<unsigned int> tindex;
      std::vector<unsigned int> nindex;
      GState* mat;
   };

   void load( std::vector< safe_ptr<GeoSet> >& gset, const std::string& filename, bool flat = false )
   {
      std::vector< Vec3<float> > verts;
      std::vector< Vec2<float> > texcoords;
      std::vector< Vec3<float> > normals;
      //std::vector< Vec4<float> > colors;
//      std::vector<unsigned int> cindex;
//      std::vector<unsigned int> tindex;
//      std::vector<unsigned int> nindex;
      std::vector< safe_ptr<GState> > materials;
      GState* currentGState = NULL;
      //GState* oldGState = NULL;
      int num_of_matches( 0 );
      std::string filetext, temptext, currentWorkingDir;
      
      std::map<std::string, Indicies> lookup;
      
      std::cout<<"Loading: \""<<filename<<"\"\n"<<std::flush;
      std::fstream dataFile;
      dataFile.open( filename.c_str(), std::ios::in );
      assert( dataFile.good() && "couldn't open .obj file" );
      CFileIO::getAll( dataFile, filetext );
      dataFile.close();

      try 
      {

         regexx::Regexx getWorkingDir;
         num_of_matches = getWorkingDir.exec( filename,"[/]?([^/]+[/]+)+", regexx::Regexx::global);
         if (num_of_matches)
         {
            currentWorkingDir = getWorkingDir.match[0];
            std::cout<<"- Current dir is: "<<currentWorkingDir<<"\n"<<std::flush;
         }

         // parse line by line
         regexx::Regexx matchOneLine;
         num_of_matches = matchOneLine.exec( filetext,"([^\n]*[\n])", regexx::Regexx::global);
         filetext = "";
         for (int lines = 0; lines < matchOneLine.match.size();  ++lines)
         {
            std::string oneLine = matchOneLine.match[lines].atom[0];
      
            //std::cout<<"one: "<<oneLine<<"\n"<<flush;
            regexx::Regexx removeComments;
            oneLine = removeComments.replace( oneLine, "#[^\n]*\n", "", regexx::Regexx::global | regexx::Regexx::newline);
         
            // load material
            // mtllib ./rects2.mtl
            regexx::Regexx extractMaterial;
            num_of_matches = extractMaterial.exec( oneLine,"mtllib[ ]+([^\n]*)", regexx::Regexx::global);
            if (num_of_matches)
            {
               loadMaterialLib( materials, currentWorkingDir, extractMaterial.match[0].atom[0].str() );
            }

            
            // use material
            // usemtl blue_material
            regexx::Regexx useMaterial;
            num_of_matches = useMaterial.exec( oneLine,"usemtl[ ]+([^ ^\n]*)", regexx::Regexx::global);
            if (num_of_matches)
            {
               lookupGState( useMaterial.match[0].atom[0].str(), materials, currentGState );
               lookup[currentGState->mapName].mat = currentGState;
            }

            // extract verts
            regexx::Regexx extractVertex;
            num_of_matches = extractVertex.exec( oneLine,"v[ ]+(.*)", regexx::Regexx::global);
            if (num_of_matches)
            {
               regexx::Regexx extractAxes;
               num_of_matches = extractAxes.exec( extractVertex.match[0].atom[0],"([0-9\\.+-]+)", regexx::Regexx::global);
               assert( num_of_matches == 3 && "this should be 3D data" );
               float x = atof( extractAxes.match[0].atom[0].str().c_str() );
               float y = atof( extractAxes.match[1].atom[0].str().c_str() );
               float z = atof( extractAxes.match[2].atom[0].str().c_str() );
         
               //std::cout<<"Vertex: "<<x<<" "<<y<<" "<<z<<"\n"<<flush;
               verts.push_back( Vec3<float>( x, y, z ) );
            }
            
            // extract tex coords
            regexx::Regexx extractTex;
            num_of_matches = extractTex.exec( oneLine,"vt[ ]+(.*)", regexx::Regexx::global);
            if (num_of_matches)
            {
               regexx::Regexx extractAxes;
               num_of_matches = extractAxes.exec( extractTex.match[0].atom[0],"([0-9\\.+-]+)", regexx::Regexx::global);
               assert( (num_of_matches == 2 || num_of_matches == 3 ) && "this should be 2D data" );
               float x = atof( extractAxes.match[0].atom[0].str().c_str() );
               float y = atof( extractAxes.match[1].atom[0].str().c_str() );
               
               //std::cout<<"TexCoord: "<<x<<" "<<y<<"\n"<<flush;
               texcoords.push_back( Vec2<float>( x, y ) );
            }
            
            // extract normals
            regexx::Regexx extractNorm;
            num_of_matches = extractNorm.exec( oneLine,"vn[ ]+(.*)", regexx::Regexx::global);
            if (num_of_matches)
            {
               regexx::Regexx extractAxes;
               num_of_matches = extractAxes.exec( extractNorm.match[0].atom[0],"([0-9\\.+-]+)", regexx::Regexx::global);
               assert( num_of_matches == 3 && "this should be 3D data" );
               float x = atof( extractAxes.match[0].atom[0].str().c_str() );
               float y = atof( extractAxes.match[1].atom[0].str().c_str() );
               float z = atof( extractAxes.match[2].atom[0].str().c_str() );
         
               //std::cout<<"Normal: "<<x<<" "<<y<<" "<<z<<"\n"<<flush;
               normals.push_back( Vec3<float>( x, y, z ) );
            }

            // extract faces
            regexx::Regexx extractFace;
            num_of_matches = extractFace.exec( oneLine,"f[ ]+(.*)", regexx::Regexx::global);
            if (num_of_matches)
            {
               std::string match = extractFace.match[0].atom[0];
               //std::cout<<"For: "<<oneLine.c_str()<<"\n"<<flush;
               //std::cout<<"     matched: "<<match.c_str()<<"\n"<<flush;
            
               regexx::Regexx extractIndicies;
               num_of_matches = extractIndicies.exec( match,"([0-9/]+)", regexx::Regexx::global);
               int numVerts = extractIndicies.match.size();
               //std::cout<<"     detected polygon with "<<numVerts<<" vertices\n"<<flush;
            
               for (int x = 0; x < numVerts; ++x)
               {
                  std::string index = extractIndicies.match[x].atom[0];
                  //std::cout<<"     matched: "<<index.c_str()<<"\n"<<flush;
                  regexx::Regexx extractNumber;
                  num_of_matches = extractNumber.exec( index,"([0-9]+)[/]?([0-9]*)[/]?([0-9]*)", regexx::Regexx::global);
                  int v = atoi( extractNumber.match[0].atom[0].str().c_str() );
                  int vt = atoi( extractNumber.match[0].atom[1].str().c_str() );
                  int vn = atoi( extractNumber.match[0].atom[2].str().c_str() );
            
                  // TODO: do a sanity check like this one later (not here).
                  //assert( (v - 1) < verts.size() );
                  //std::cout<<(vt - 1)<<" "<<texcoords.size()<<"\n"<<flush;
                  //assert( (vt - 1) < texcoords.size() );
                  //assert( (vn - 1) < normals.size() );
                  
                  if (currentGState != NULL)
                  {
                     lookup[currentGState->mapName.c_str()].cindex.push_back( v - 1 );
                     lookup[currentGState->mapName.c_str()].tindex.push_back( vt - 1 );
                     lookup[currentGState->mapName.c_str()].nindex.push_back( vn - 1 );
                  }
                  else
                  {
                     lookup["notex"].cindex.push_back( v - 1 );
                     lookup["notex"].tindex.push_back( vt - 1 );
                     lookup["notex"].nindex.push_back( vn - 1 );
                  }               
               }
            }
         }
      }
      catch (regexx::Regexx::CompileException &e)
      {
         std::cerr << e.message().c_str() << std::endl;
      }

      // dump the info into geosets...
      std::map< std::string, Indicies >::iterator it;
      for (it = lookup.begin(); it != lookup.end(); ++it)
      {
         std::cout<<"- Building "<<(*it).first<<" geoset\n"<<std::flush;
            
         GeoSet* geoset = new GeoSet;

         // set the name
         geoset->setName( filename );

         
         Vec4<float> color( 1.0f,1.0f,1.0f,1.0f );

         //std::cout<<"- coords == "<<lookup[(*it).first].cindex.size()<<"\n"<<std::flush;
         //std::cout<<"- normals == "<<lookup[(*it).first].nindex.size()<<"\n"<<std::flush;
         //std::cout<<"- texcoords == "<<lookup[(*it).first].tindex.size()<<"\n"<<std::flush;
         
         geoset->setPrimType( GeoSet::TRIS );
         geoset->setNumPrims( lookup[(*it).first].cindex.size() / 3 );
         geoset->allocate();
         geoset->setAttr( GeoSet::COORD3, GeoSet::PER_VERTEX, (void*)&verts[0], (unsigned int*)&lookup[(*it).first].cindex[0] );
         geoset->setAttr( GeoSet::COLOR4, GeoSet::OVERALL, (void*)&color[0], NULL );
         if (normals.size() > 0 && lookup[(*it).first].nindex.size() > 0)
            geoset->setAttr( GeoSet::NORMAL3, GeoSet::PER_VERTEX, (void*)&normals[0], (unsigned int*)&lookup[(*it).first].nindex[0] );
         else
            std::cout<<"  - Not enough normals.  total normals = "<<normals.size()<<", indecies == "<<lookup[(*it).first].nindex.size()<<"\n"<<std::flush;
         geoset->setAttr( GeoSet::TEXCOORD2, GeoSet::PER_VERTEX, (void*)&texcoords[0], (unsigned int*)&lookup[(*it).first].tindex[0] );

         if (lookup[(*it).first].mat != NULL)
         {
            std::cout<<"  - Setting texture: "<<(*it).first<<" to new geoset\n"<<std::flush;
            geoset->setGstate( lookup[(*it).first].mat );
         }
         
         gset.push_back( geoset );
      }            
   }
   
   void buildGeoSet()
   {
      
   }

};

}// end namespace

#endif
