#ifndef HUD_INCLUDED
#define HUD_INCLUDED

#include "GeoSet.h"
#include "PixmapFont.h"
#include "PixmapFontImporter.h"
#include "TextToGeoSet.h"

// simple HUD, just text for now...
// todo, maybe allow the application to create widgets, i.e. register 
// a text string and recieve a handle to it, then it can set pos and string info
// on it.
class HUD // TextHUD
{
public:
   HUD()
   {
	  mText = new GeoSet;
      mText->setName( "HUD text" );
      mPlayerPos = new GeoSet;
      mPlayerPos->setName( "HUD PlayerPos" );

      mPlayerPos->ref();
      mText->ref();
   }
   
   void init()
   {
      kev::PixmapFontImporter::import( "models/quake3.font", mFont );
      
      Vec3<float> text_color( 0.7f, 0.7f, 1.0f );
      kev::TextToGeoSet::convert( "SpaceTank", mFont, text_color, *mText );
   }
   
   ~HUD()
   {
      //std::cout<<"deleting hud... "<<"\n"<<std::flush;
      mPlayerPos->unref();
      mText->unref();
   }
      
   void draw()
   {
      glPushAttrib( GL_ENABLE_BIT );
      glDisable( GL_LIGHTING );
      {      
         glMatrixMode( GL_PROJECTION );
         glPushMatrix();
            glLoadIdentity();
            glOrtho( 0, 640, 0, 480, 100, -100 ); // hard coded...
            glMatrixMode( GL_MODELVIEW );
            glPushMatrix();
            {
               glLoadIdentity();
               glTranslatef( 0, -1, 0 );
               glPushMatrix();
                  glScalef( 2, 2, 2 );
                  kev::glRenderGeoSet( *mText );
               glPopMatrix();
               
               glTranslatef( 300, -1, 0 );
               glScalef( 2, 2, 2 );
               kev::glRenderGeoSet( *mPlayerPos );
            }
            glPopMatrix();

         glMatrixMode( GL_PROJECTION );
         glPopMatrix();

         glMatrixMode( GL_MODELVIEW ); 
      }      
      glPopAttrib();
   }
   
   void setPlayerPos( float x, float y, float z )
   {
      char buf[40];
      sprintf( buf, "%d, %d, %d", (int)x, (int)y, (int)z );
      Vec3<float> text_color( 1.0f, 0.7f, 0.7f );
      kev::TextToGeoSet::convert( buf, mFont, text_color, *mPlayerPos );
   }   
   
   GeoSet* mText, *mPlayerPos;
   kev::PixmapFont mFont;
};

#endif
