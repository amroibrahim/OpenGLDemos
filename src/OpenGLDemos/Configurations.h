#pragma once

#include <SDL.h>
#include <cstdint>

#include "LogGUI.h"

// Display settings
struct Display
{
  int screen_buffer_width = 1280;
  int screen_buffer_height = 720;

  int back_buffer_width = 1280;
  int back_buffer_hight = 720;

  float framerate = 60;

  SDL_Window* window;
};

// Render settings
struct Render
{
  float render_clear_color_r = 0;
  float render_clear_color_g = 0;
  float render_clear_color_b = 0;
  SDL_Renderer* renderer;
};

struct Subsystems
{
  Display display;
  Render render;
  LogGUI logger;
};
