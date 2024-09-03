#pragma once

#include <SDL.h>

#include "SettingsGUI.h"

#include "Scene.h"
#include "ScenesManager.h"

class SDLApp
{
public:
  SDLApp();
  void Initialize();

  virtual ~SDLApp();

  void ProcessInput();
  void Render();
  void Update();
  void Delay();
  void Quit();
  void Clean();

  bool IsOver();

protected:
  void KeyPress(const Uint8* key_states);
  void SwitchSceneOnSelection();

  SDL_GLContext _gl_context;
  SDL_Window* _window;
  Subsystems _configuration;
  SettingsGUI _settings_gui;
  ScenesManager _scenes_manager;
  Scene* _current_scene;
  int _current_scene_index;

  uint32_t _frame_length;
  uint32_t _last_frame_time;

  int _screen_width;
  int _screen_height;
  bool _is_over;
};

