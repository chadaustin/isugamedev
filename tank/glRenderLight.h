
#ifdef WIN32
   #include <windows.h>
   //	#include <afxwin.h> // for WING opengl stuff
#endif
#include <GL/gl.h>    //for opengl
#include <GL/glu.h>   //for opengl

#include <assert.h>

#include "Light.h"

void glRender( const Light& light )
{
    int lightNumber = GL_LIGHT0;

    // figure out which GL light number the light is...
    switch (light.number())
    {
    case 0: lightNumber = GL_LIGHT0; break;
    case 1: lightNumber = GL_LIGHT1; break;
    case 2: lightNumber = GL_LIGHT2; break;
    case 3: lightNumber = GL_LIGHT3; break;
    case 4: lightNumber = GL_LIGHT4; break;
    case 5: lightNumber = GL_LIGHT5; break;
    case 6: lightNumber = GL_LIGHT6; break;
    case 7: lightNumber = GL_LIGHT7; break;
    default:
	// light number has to be in the range [0,7] 
	// when rendering with OpenGL.
	std::cout<<"light number "<<light.number()<<" has to be in the range [0,7]\n"<<std::flush;
	assert(light.number()>=0 && light.number()<=7);
	lightNumber = GL_LIGHT0; break;
    }

    if (light.isOn())
{
    // gather the data to be used to setup the opengl light.
    float ambient[3], diffuse[3], specular[3], position[4];
    float constantAttenuation, linearAttenuation, quadraticAttenuation;
    float cutoff, direction[3], exponent;
    light.getColor( Light::ambient, ambient[0], ambient[1], ambient[2] );
    light.getColor( Light::diffuse, diffuse[0], diffuse[1], diffuse[2] );
    light.getColor( Light::specular, specular[0], specular[1], specular[2] );
    light.getPos( position[0], position[1], position[2], position[3] );
    light.getAtten( constantAttenuation, linearAttenuation, quadraticAttenuation );
    light.getSpotDir( direction[0], direction[1], direction[2] );
    light.getSpotCone( exponent, cutoff );

    // light color.
    glLightfv(lightNumber, GL_AMBIENT, ambient);
    glLightfv(lightNumber, GL_DIFFUSE, diffuse);
    glLightfv(lightNumber, GL_SPECULAR, specular);

    // position
    glLightfv(lightNumber, GL_POSITION, position);
    
    // attenuation
    glLightfv(lightNumber, GL_CONSTANT_ATTENUATION, &constantAttenuation);
    glLightfv(lightNumber, GL_LINEAR_ATTENUATION, &linearAttenuation);
    glLightfv(lightNumber, GL_QUADRATIC_ATTENUATION, &quadraticAttenuation);
    
    // spotlight
    glLightfv( lightNumber, GL_SPOT_CUTOFF, &cutoff );
    glLightfv( lightNumber, GL_SPOT_DIRECTION, direction );
    glLightfv( lightNumber, GL_SPOT_EXPONENT, &exponent );

    glEnable( lightNumber );
    
    const float thisIsFalse[] = { GL_FALSE };
    //const float thisIsTrue[] = { GL_TRUE };
    glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, thisIsFalse);
    glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, thisIsFalse);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
}
else
{
    glDisable( lightNumber );
}

}
