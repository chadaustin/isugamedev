#ifndef GRID_INCLUDED
#define GRID_INCLUDED

class Grid
{
public:
   Grid()
   {
      size = 10;
      this->setPos( 0.0f, 0.0f, 0.0f );
      this->setColor( 0.3f, 0.2f, 0.6f );
   }
   void draw()
   {
      glColor3f( color[0], color[1], color[2] );
      glPushMatrix();
      glTranslatef( position[0], position[1], position[2] );
      glBegin( GL_LINES );
         for ( float x = -size; x < size; ++x)
         {
            glVertex3f( -size, 0, x );
            glVertex3f(  size, 0, x );
            glVertex3f( x, 0, -size );
            glVertex3f( x, 0,  size );
         }
      glEnd();
      glPopMatrix();
   }
   float size;
   void setPos( float x, float y, float z )
   {
      position[0] = x;
      position[1] = y;
      position[2] = z;
   }
   void setColor( float r, float g, float b )
   {
      color[0] = r;
      color[1] = g;
      color[2] = b;
   }   
   float position[3];
   float color[3];
};

#endif
