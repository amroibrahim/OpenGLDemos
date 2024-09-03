#pragma once

#include <string>

#include <SDL.h>

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include "Configurations.h"

class SettingsGUI
{
public:
  SettingsGUI(Subsystems* configuration);
  void Initialize(SDL_Window* window, SDL_GLContext gl_context, std::string scenes_list);
  void ProcessEvent(SDL_Event* event);
  void Update();
  void Render();
  void Clean();
  void SetSceneSelection(int scene_index);
  int GetSceneSelection();

protected:
  void BuildWindows();
  void MainSettingsWindow();

  bool _show_log_window;
  int _scene_selection;
  std::string _scenes_list;
  ImVec4 _clear_color;
  Subsystems* _configuration;
  SDL_Window* _window;
};

