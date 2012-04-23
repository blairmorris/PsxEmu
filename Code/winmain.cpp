#include "display_window.h"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  MSG msg;
  my_app::DisplayWindow display_window;
  //void read_iso_cd();
  //read_iso_cd();

  display_window.Initialize();

  do {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    } else {
      display_window.Step();
    }
  } while(msg.message!=WM_QUIT);
 
   //Return the exit code to the system. 
   return static_cast<int>(msg.wParam);
}