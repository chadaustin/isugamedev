/////////////////////////////////////
// Copyright Levi VanOort 4-19-2002
//		lvanoort@aol.com
//	Released under MIT 
//
// GraphicsObject.h
/////////////////////////////////////

#ifndef __GRAPHICSOBJECT_H__
#define __GRAPHICSOBJECT_H__

class GraphicsObject
{
public:
	virtual void Draw() = 0;
	virtual void Init() = 0;


   ////////////////////////////////
   // Common Set functions
   ////////////////////////////////
   void SetCenter(float Center[3])
   {
      for(int i = 0; i < 3; i++)
         ObjectCenter[i] = Center[i];
   }

   void SetRotate(float Rotate[3])
   {
      for(int i = 0; i < 3; i++)
         ObjectRotate[i] = Rotate[i];
   }

   //////////////////////////////////
   // Common Get functions
   //////////////////////////////////
   void GetCenter(float Center[3])
   {
      for(int i = 0; i < 3; i++)
         Center[i] = ObjectCenter[i];
   }
   void GetRotate(float Rotate[3])
   {
      for(int i = 0; i < 3; i++)
         Rotate[i] = ObjectRotate[i];
   }
private:
   float ObjectCenter[3];
   float ObjectRotate[3];
};
#endif