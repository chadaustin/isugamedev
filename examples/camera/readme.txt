Readme for simple camera.

This is a Visual studio build of the first camera class.  I'm pretty sure it won't 
build on other platforms but, if you're really smart (you probably are) and you have
time (and I don't) then you can write your own makefiles and give it a spin.  

The way this camera works is that all the movements that the camera makes are
in respect to the camera, so if we spin the camera to the left it is going to spin 
around the center of the camera in the xz plane of the camera, not the xz plane of 
the world.  Tilting the camera works the same way.  If you tilt the camera down, it 
tilts it down in respect to the camera.  

The way to use theis class is to include the camera class in an application.  
You initialize a camera object and then you call the varios methods in the camera
class to move the position of the camera about the world.  Then after you have moved 
the camera you need to redraw the scene with the camera in the new position
so you call camera.update, which puts onto the matrix stack the inverse of the 
position of the camera, or the way the world needs to look as if it where being
looked at through a camera.

I wrote an app that draws a cube to the screen and lets you move the camera around the
world which contains a cube object and a grid.  

The following table is the current key mapping, but you can adjust as you need to for
your app.

Key			|		direction
a			=	moves camera left relative to current orientation
d			=	moves camera right relative to current orientation
w			=	moves camera up relative to current orientation
x			=	moves camera down relative to current orientation
q			=	moves camera into the screen 
z			=	moves camera out of the screen
left arrow	=	rotate camera left
down arrow	=	tilt camera up
right arrow =	rotate camera right
up arrow	=	tilt camera down	
