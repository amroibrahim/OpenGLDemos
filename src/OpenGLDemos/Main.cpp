
#include <iostream>
#include <memory>

#include "SDLApp.h"


int main(int argc, char* argv[])
{
  std::unique_ptr<SDLApp> pDemoScenes = std::make_unique<SDLApp>();

  pDemoScenes->Initialize();

  while (!pDemoScenes->IsOver())
  {
    pDemoScenes->ProcessInput();
    pDemoScenes->Update();
    pDemoScenes->Render();
    pDemoScenes->Delay();
  }

  pDemoScenes->Clean();

  return 0;
}

