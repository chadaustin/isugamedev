/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************** brotha-head beg
 *
 * Warn-a-Brotha
 *
 * Original Authors:
 *    Chad Austin <aegis@aegisknight.org>
 *    Josh Carlson <josh@chegg.com>
 *    Jeremy Hanson <jjhanson@iastate.edu>
 *    Chad Okere <cokere@hatori42.com>
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: Win32PrintingEngine.cpp,v $
 * Date modified: $Date: 2002-04-30 09:33:15 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 *********************************************************** brotha-head-end */
/*************************************************************** brotha-cpr beg
 *
 * Warn-a-Brotha
 * Warn-a-Brotha is (C) Copyright 2002 by
 *    Chad Austin, Josh Carlson, Jeremy Hanson, Chad Okere, Ben Scott
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
 ************************************************************ brotha-cpr-end */

#include <windows.h>
#include <GL/gl.h>
#include <iostream>
#include "PrintingEngine.h"

namespace client {

   typedef unsigned char byte;
   struct BGR {
      byte blue, green, red;
   };
   
   void doPrint(const BITMAPINFO& bmi, BGR* pixels) {
   
      int width  = bmi.bmiHeader.biWidth;
      int height = bmi.bmiHeader.biHeight;
   
      PRINTDLG ppd;
      memset(&ppd, 0, sizeof(ppd));
      ppd.lStructSize = sizeof(ppd);
      ppd.Flags = PD_RETURNDC | PD_RETURNDEFAULT;
      if (!PrintDlg(&ppd)) {
         std::cerr << "error calling PrintDlg()" << std::endl;
         return;
      }
      
      HDC print_dc = ppd.hDC;
      if (!(GetDeviceCaps(print_dc, RASTERCAPS) & RC_STRETCHDIB)) {
         std::cerr << "Printer does not support StretchDIBits" << std::endl;
         goto error;
      }
      
      DOCINFO di;
      memset(&di, 0, sizeof(di));
      di.cbSize = sizeof(di);
      di.lpszDocName = "Warn-a-Brotha Screenshot";
      di.lpszOutput = 0;
      di.lpszDatatype = 0;
      di.fwType = 0;
      
      if (StartDoc(print_dc, &di) == SP_ERROR) {
         std::cerr << "StartDoc() falied" << std::endl;
         goto error;
      }
      
      if (StartPage(print_dc) <= 0) {
         std::cerr << "StartPage() failed" << std::endl;
         goto error;
      }
      
      float screenPPIX = 120;
      float screenPPIY = 120;
      
      float printerPPIX = float(GetDeviceCaps(print_dc, LOGPIXELSX));
      float printerPPIY = float(GetDeviceCaps(print_dc, LOGPIXELSY));
      
      float scaleX = screenPPIX > printerPPIX ?
                     screenPPIX / printerPPIX :
                     printerPPIX / screenPPIX;
      float scaleY = screenPPIY > printerPPIY ?
                     screenPPIY / printerPPIY :
                     printerPPIY / screenPPIY;

      int cWidthPels  = GetDeviceCaps(print_dc, HORZRES);
      int cHeightPels = GetDeviceCaps(print_dc, VERTRES);
      int left = ((cWidthPels  / 2) - int(float(width)  * scaleX / 2));
      int top  = ((cHeightPels / 2) - int(float(height) * scaleY / 2));
      
      int result = StretchDIBits(
         print_dc, left, top,
         int(width * scaleX), int(height * scaleY),
         0, 0, width, height, pixels,
         &bmi, DIB_RGB_COLORS, SRCCOPY);
      if (result == GDI_ERROR) {
         std::cerr << "StretchDIBits() failed" << std::endl;
         goto error;
      }
            
      if (EndPage(print_dc) <= 0) {
         std::cerr << "EndPage() failed" << std::endl;
         goto error;
      }
      
      if (EndDoc(print_dc) <= 0) {
         std::cerr << "EndDoc() failed" << std::endl;
         goto error;
      }
      
error:
      DeleteDC(print_dc);
   }

   void PrintingEngine::print() {
   
      // get the dimensions of the current viewport
      GLint viewport[4];
      glGetIntegerv(GL_VIEWPORT, viewport);
      int width  = viewport[2];
      int height = viewport[3];
      
      // create a DIB section to read the pixels into
      
      HDC dc = CreateCompatibleDC(0);
      if (!dc) {
         std::cerr << "error calling CreateCompatibleDC()" << std::endl;
         return;
      }
      
      BITMAPINFO bmi;
      memset(&bmi, 0, sizeof(bmi));
      BITMAPINFOHEADER& bmih = bmi.bmiHeader;
      bmih.biSize        = sizeof(bmih);
      bmih.biWidth       = width;
      bmih.biHeight      = height;
      bmih.biPlanes      = 1;
      bmih.biBitCount    = 24;
      bmih.biCompression = BI_RGB;
      
      BGR* pixels;
      HBITMAP bitmap = CreateDIBSection(
         ::GetDC(0), &bmi, DIB_RGB_COLORS, (void**)&pixels, NULL, 0);
      if (!bitmap) {
         std::cerr << "error calling CreateDIBSection()" << std::endl;
         DeleteDC(dc);
         return;
      }
      
      // read the pixels from the framebuffer      
      glReadPixels(0, 0, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
      
      // send the pixels to the printer
      doPrint(bmi, pixels);
      
      // clean up
      DeleteObject(bitmap);
      DeleteDC(dc);
   }
   
}
