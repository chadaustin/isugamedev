
//////////////////////////////////////////////////////////////////////////////
//
//                       -=    RGBA Color    =-
//
// Description: "Color vector class."
//
///////////////// <auto-copyright BEGIN do not edit this line> /////////////////
//
//    $RCSfile: ColorRGBA.cpp,v $
//    $Date: 2002-05-05 17:07:40 $
//    $Revision: 1.5 $
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

//////////////////////////////////////////////////////////////////////////////
#include "ColorRGBA.h"
namespace kev
{

//	Default Constructor
ColorRGBA::ColorRGBA()
{
	mChannel[0] = 0.0f;
	mChannel[1] = 0.0f;
	mChannel[2] = 0.0f;
	mChannel[3] = 1.0f;
}


//	INTEGER Constructor.
ColorRGBA::ColorRGBA( const unsigned int& red, const unsigned int& green, const unsigned int& blue, const unsigned int& alpha )
{
	float factor = 1.0f / 255.0f;

	mChannel[0] = ((float) red) * factor;
	mChannel[1] = ((float) green) * factor;
	mChannel[2] = ((float) blue) * factor;
	mChannel[3] = ((float) alpha) * factor;

	this->validate();
}

//	INTEGER Constructor.
ColorRGBA::ColorRGBA( const int& red, const int& green, const int& blue, const int& alpha )
{
	float factor = 1.0f / 255.0f;

	mChannel[0] = ((float) red) * factor;
	mChannel[1] = ((float) green) * factor;
	mChannel[2] = ((float) blue) * factor;
	mChannel[3] = ((float) alpha) * factor;

	this->validate();
}


//	Constructor.
ColorRGBA::ColorRGBA( const float& red, const float& green, const float& blue, const float& alpha )
{
	mChannel[0] = red;
	mChannel[1] = green;
	mChannel[2] = blue;
	mChannel[3] = alpha;

	this->validate();
}

//	Copy Constructor.
ColorRGBA::ColorRGBA( const ColorRGBA& color ) 
{
	mChannel[0] = color.red();
	mChannel[1] = color.green();
	mChannel[2] = color.blue();
	mChannel[3] = color.alpha();

	this->validate();
}

//: Copy constructor for vector
ColorRGBA::ColorRGBA( const Vec4<float>& color )
{
	mChannel = color;

	this->validate();
}


//	Constructor.
ColorRGBA::ColorRGBA( const unsigned int& rgb, const float& alpha )
{
	unsigned int red =   ( ( rgb & 0x000000FF ) >> 0 );
	unsigned int green = ( ( rgb & 0x0000FF00 ) >> 8 );
	unsigned int blue =  ( ( rgb & 0x00FF0000 ) >> 16 );
	
	float factor = 1.0f / 255.0f;

	mChannel[0] = ((float) red) * factor;
	mChannel[1] = ((float) green) * factor;
	mChannel[2] = ((float) blue) * factor;
	mChannel[3] = alpha;
}

//  Get the color.
void ColorRGBA::getInteger ( unsigned int& rgb ) const 
{ 
	unsigned int red =   (unsigned int) (mChannel[0] * 255.0f);
	unsigned int green = (unsigned int) (mChannel[1] * 255.0f);
	unsigned int blue =  (unsigned int) (mChannel[2] * 255.0f);

	rgb = ( red << 0 ) | ( green << 8 ) | ( blue << 16 );
}

//  Get the color.
void ColorRGBA::get( float &red, float &green, float &blue ) const 
{ 
	red =   mChannel[0];
	green = mChannel[1];
	blue =  mChannel[2];
}

//  Get the color.
void ColorRGBA::get( float &red, float &green, float &blue, float &alpha ) const 
{ 
	red =   mChannel[0];
	green = mChannel[1];
	blue =  mChannel[2];
	alpha = mChannel[3];
}
	
//  Sets the ColorRGBA on the left (*this) of the "=" equal to the 
//  one on the right (color).
const ColorRGBA& ColorRGBA::operator=( const ColorRGBA& color )
{
	mChannel[0] = color[0];
	mChannel[1] = color[1];
	mChannel[2] = color[2];
	mChannel[3] = color[3];

	this->validate();

	return *this; 
}

//  Set the rgba value.
void ColorRGBA::set( const float& red, const float& green, const float& blue, const float& alpha ) 
{
	mChannel[0] = red;
	mChannel[1] = green;
	mChannel[2] = blue;
	mChannel[3] = alpha;

	this->validate();
}

//  Set the rgba value.
void ColorRGBA::setInteger( const int& red, const int& green, const int& blue, const int& alpha ) 
{
	float factor = 1.0f / 255.0f;

	mChannel[0] = ((float) red) * factor;
	mChannel[1] = ((float) green) * factor;
	mChannel[2] = ((float) blue) * factor;
	mChannel[3] = ((float) alpha) * factor;

	this->validate();
}

//  Set the rgba value.
void ColorRGBA::setInteger ( const unsigned int& red, const unsigned int& green, 
						   const unsigned int& blue, const unsigned int& alpha ) 
{
	float factor = 1.0f / 255.0f;

	mChannel[0] = ((float) red) * factor;
	mChannel[1] = ((float) green) * factor;
	mChannel[2] = ((float) blue) * factor;
	mChannel[3] = ((float) alpha) * factor;

	this->validate();
}

//  Set the rgba value.
void ColorRGBA::set( const ColorRGBA &color ) 
{
	mChannel[0] = color[0];
	mChannel[1] = color[1];
	mChannel[2] = color[2];
	mChannel[3] = color[3];

	this->validate();
}

//  Set the color.
void ColorRGBA::setInteger ( const unsigned int& rgb, const float& alpha ) 
{
	unsigned int red =   ( ( rgb & 0x000000FF ) >> 0 );
	unsigned int green = ( ( rgb & 0x0000FF00 ) >> 8 );
	unsigned int blue =  ( ( rgb & 0x00FF0000 ) >> 16 );
	
	float factor = 1.0f / 255.0f;

	mChannel[0] = ((float) red) * factor;
	mChannel[1] = ((float) green) * factor;
	mChannel[2] = ((float) blue) * factor;
	mChannel[3] = alpha;
}

	
//  Make sure the values are in range.
void ColorRGBA::validate() 
{
	if		( mChannel[0] > 1.0f ) mChannel[0] = 1.0f;
	else if ( mChannel[0] < 0.0f ) mChannel[0] = 0.0f;

	if		( mChannel[1] > 1.0f ) mChannel[1] = 1.0f;
	else if ( mChannel[1] < 0.0f ) mChannel[1] = 0.0f;

	if		( mChannel[2] > 1.0f ) mChannel[2] = 1.0f;
	else if ( mChannel[2] < 0.0f ) mChannel[2] = 0.0f;

	if		( mChannel[3] > 1.0f ) mChannel[3] = 1.0f;
	else if ( mChannel[3] < 0.0f ) mChannel[3] = 0.0f;
}

//  Output operator.
std::ostream& operator<<( std::ostream &out, const ColorRGBA &color )
{
	out << color[0] << " " 
		<< color[1] << " " 
		<< color[2] << " " 
		<< color[3];

	return out;
}

//  Input operator.
std::istream& operator>>( std::istream &in, ColorRGBA &color )
{
	in >> color[0] 
	   >> color[1] 
	   >> color[2] 
	   >> color[3];

	return in;
}

//  Get the hsv.
void ColorRGBA::getHSV ( float &hue, float &saturation, float &value ) const
{
	ColorRGBA::RGB2HSV ( mChannel[0], mChannel[1], mChannel[2], hue, saturation, value );
}

//  Set the hsv.
void ColorRGBA::setHSV ( const float& hue, const float& saturation, const float& value, const float& alpha)
{
	ColorRGBA::HSV2RGB( hue, saturation, value, mChannel[0], mChannel[1], mChannel[2] );
	mChannel[3] = alpha;
}

} // end namespace kev
