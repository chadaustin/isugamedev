Chad Austin
ME 519 - Final Project
2002.05.05


-- Basic Stuff --

This project was a lot of fun.  :) I think it turned out pretty well
too.  I learned a lot about rendering terrains for Battlements.

This application supports creating textures in three distinct ways:
using plasma subdivision, from a heightmap image (using the luminance
of pixels as height), and using a plasma subdivision-like method that
I wrote.  The terrain generation method is passed as arguments to the
command line.  Run terrain.exe without any arguments for instructions.

I also have three different cameras.  The Rotation Camera views the
terrain from a distance.  If you press the left and right arrow keys,
you can rotate the world to see it from a different angle.  The Fly
Camera and Hover Camera both use A and Z to move up and down, Up and
Down to move forwards and backwards, and Left and Right to turn to the
left and to the right.  The difference between FlyCam and HoverCam is
that the hover camera is always a fixed distance from the terrain.
Press C to switch between them.

Level of detail support is rather straightforward.  If you increase
the Detail Reduction from 1 to 2, the renderer simply skips every
intermediate vertex.  If you increase it to the 3, it skips every two
intermediate vertices.  Press + and - to increase or decrease the
detail reduction level.

The terrain is rendered in three passes.  One pass draws the base
grass part of the texture.  The other two draw snow and the base
ground.  I could use multitexturing, but that isn't standard until
OpenGL 1.2, which I don't have headers for in Windows.  ;)  I'm sure
I'll switch to multitexturing for the production version.

I created all of the textures myself using the GIMP.


-- Nifty Stuff --

There's a little particle engine in there...  I thought some snow
would look good.  :)

Fog!  It's trivial to do in OpenGL!

I also added some ambient wind in the background.  There are two
looping sounds, and the application gradually crossfades between them.
Sounds add quite a lot of atmosphere to these things.


-- Optimization --

At first I drew every quad in the terrain using individual quads.  I
switched to quad strips, and noticed about a 30% speed improvement.
Unfortunately, when I started texturing the quads, I had to remove the
quad strips and just use quads (or triangle fans) again.  :( I
recently upgraded the texturing to stretch a single texture across
several quads, and in this case I could use at least short quad
strips.  I'll probably experiment with this in the production version
as well.

As mentioned earlier, I need to use multitexturing.  I bet that will
give massive speedups.


-- Technologies --

Loading textures and heightmap images with Corona
<http://aegisknight.org/corona>.

Sound playback using Audiere <http://aegisknight.org/audiere>.

GLUT and OpenGL, of course.  :)


-- Binary Files --

terrain.exe - Main executable

*.bat - Several batch files to start the program using different
terrain generation settings

audiere.dll - Audiere Sound System DLL

corona.dll - Corona Image I/O DLL

*.ogg - Wind sound effects found on apple.com

{terrain{1,2,3,4},gradient}.png - Example heightmap images

{grass,ground,snow}.png - Textures used in terrain renderer


-- Source Files --

AmbientWind.{cpp,h} - Controls behavior of ambient wind noise.

Main.cpp - Entry point of application, sets up GLUT and creates
TerrainApplication object.

Application.h - Basic Application interface that GLUT interfaces with.
This application only has one implementation of this interface.

TerrainApplication.{cpp,h} - The application.  :)

Math.h - Common math thingies...

Vector.h - Implementation of vector class.

Camera.h - Common camera interface.

FlyCamera.{cpp,h} - Fly Camera implementation.

HoverCamera.{cpp,h} - Hover Camera implementation.

RotationCamera.{cpp,h} - Rotation Camera implementation.

Terrain.h - Common terrain generation interface.

ImageTerrain.{cpp,h} - Heightmap image terrain implementation.

MyTerrain.{cpp,h} - My image terrain implementation.

PlasmaTerrain.{cpp,h} - Plasma subdivision terrain implementation.

Texture.{cpp,h} - OpenGL wrapper for Corona that creates a texture
object.

SConstruct,glut_libs.py - SCons build system for Cygwin and Linux (and
presumably IRIX).

terrain.{sln,vcproj} - VC7 build system.
