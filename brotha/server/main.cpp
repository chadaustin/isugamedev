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
 * File:          $RCSfile: main.cpp,v $
 * Date modified: $Date: 2002-04-28 16:41:06 $
 * Version:       $Revision: 1.10 $
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
// Win32-only server

#include <string>
#include <windows.h>
#include "resource.h"
#include "util/HWNDstream.h"
#include "BrothaServer.h"


server::BrothaServer g_BrothaServer;

LRESULT CALLBACK WndProc(HWND wnd, UINT msg, WPARAM wParam, LPARAM lParam) {
   static HWND wndLog;

   switch(msg) {
      case WM_CREATE: {
         wndLog = CreateWindow("edit", NULL, WS_CHILD | //WS_DISABLED |
               WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_BORDER | ES_LEFT | 
               ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 0, 0,
               wnd, (HMENU)1, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

         HMENU menu = GetMenu(wnd);
         EnableMenuItem(menu, ID_SERVER_STOP, MF_GRAYED);
         EnableMenuItem(menu, ID_WEBSERVER_STOP, MF_GRAYED);

//         util::log = new util::HWNDostream(wndLog);
      } return 0;
      case WM_SIZE:
         MoveWindow(wndLog, 0, 0, LOWORD(lParam), HIWORD(lParam), true);
         return 0;
      case WM_DESTROY:
         PostQuitMessage(0);
         return 0;
      case WM_COMMAND: {
         HMENU menu = GetMenu(wnd);
         switch(LOWORD(wParam)) {
            case ID_SERVER_START:
               EnableMenuItem(menu, ID_SERVER_START, MF_GRAYED);
               EnableMenuItem(menu, ID_SERVER_STOP, MF_ENABLED);
               g_BrothaServer.StartServer();
               break;
            case ID_SERVER_STOP:
               EnableMenuItem(menu, ID_SERVER_START, MF_ENABLED);
               EnableMenuItem(menu, ID_SERVER_STOP, MF_GRAYED);
               g_BrothaServer.StopServer();
               break;
            case ID_SERVER_SETTINGS:
               break;
            case ID_WEBSERVER_START:
               EnableMenuItem(menu, ID_WEBSERVER_START, MF_GRAYED);
               EnableMenuItem(menu, ID_WEBSERVER_STOP, MF_ENABLED);
               g_BrothaServer.StartWebServer();
               break;
            case ID_WEBSERVER_STOP:
               EnableMenuItem(menu, ID_WEBSERVER_START, MF_ENABLED);
               EnableMenuItem(menu, ID_WEBSERVER_STOP, MF_GRAYED);
               g_BrothaServer.StopWebServer();
               break;
         }
      } break;
   }
   return DefWindowProc(wnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, PSTR cmdLine, int cmdShow) {
   std::string appName = "WAB Server";

   WNDCLASSEX wndClass;
   wndClass.cbSize        = sizeof(wndClass);
   wndClass.style         = CS_HREDRAW | CS_VREDRAW;
   wndClass.lpfnWndProc   = WndProc;
   wndClass.cbClsExtra    = 0;
   wndClass.cbWndExtra    = 0;
   wndClass.hInstance     = instance;
   wndClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
   wndClass.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
   wndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
   wndClass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
   wndClass.lpszMenuName  = MAKEINTRESOURCE(IDR_WAB);
   wndClass.lpszClassName = appName.c_str();

   RegisterClassEx(&wndClass);

   HWND wnd = CreateWindow(appName.c_str(), appName.c_str(),
         WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 600, 400, NULL,
         NULL, instance, NULL);

   ShowWindow(wnd, cmdShow);
   UpdateWindow(wnd);

   MSG msg;
   while(GetMessage(&msg, NULL, 0, 0)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
   }
   return (int)msg.wParam;
}
