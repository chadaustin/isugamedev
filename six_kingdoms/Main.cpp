#include <windows.h>


LRESULT CALLBACK WindowProc(
  HWND window,
  UINT message,
  WPARAM wparam,
  LPARAM lparam)
{
  switch (message) {
    case WM_CLOSE: {
      DestroyWindow(window);
      return 0;
    }

    case WM_DESTROY: {
      PostQuitMessage(0);
      return 0;
    }

    default: {
      return DefWindowProc(window, message, wparam, lparam);
    }
  }
}


int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int show)
{
  // register window class
  // don't worry about failure: if this fails, CreateWindow() will
  WNDCLASS wc;
  memset(&wc, 0, sizeof(wc));
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = instance;
  wc.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_APPLICATION));
  wc.hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW));
  wc.lpszClassName = "SixKingdomsWindow";
  RegisterClass(&wc);

  HWND window = CreateWindow(
    "SixKingdomsWindow",
    "Six Kingdoms",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, 0,
    CW_USEDEFAULT, 0,
    NULL, NULL, instance, NULL);
  if (!window) {
    MessageBox(
      NULL,
      "Could not create window!",
      "Six Kingdoms",
      MB_OK | MB_ICONERROR);
    return 0;
  }

  ShowWindow(window, show);
  UpdateWindow(window);

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return msg.wParam;
}
