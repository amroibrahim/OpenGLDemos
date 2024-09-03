#pragma once

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

class LogGUI
{
public:
  void Log(const char* format, ...);
  void Render(const char* title, bool* p_opened = NULL);
  void Clear();

protected:
  ImGuiTextBuffer _log_buffer;
  ImGuiTextFilter _filter;
  ImVector<int> _line_offsets;
  bool _scroll_bottom;
};
