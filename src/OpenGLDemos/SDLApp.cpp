#include "SDLApp.h"

#include <iostream>
#include <glad/glad.h>

SDLApp::SDLApp() :
  _is_over(false),
  _screen_width(1280),
  _screen_height(720),
  _window(nullptr),
  _frame_length(10),
  _settings_gui(&_configuration),
  _scenes_manager(&_configuration)
{
  _screen_width = _configuration.display.screen_buffer_width;
  _screen_height = _configuration.display.screen_buffer_height;
  _frame_length = 1000 / _configuration.display.framerate;
}

void SDLApp::Initialize()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cout << "SDL failed to initialize! SDL_Error: " << SDL_GetError() << std::endl;
  }

  _window = SDL_CreateWindow("OpenGL Demos", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screen_width, _screen_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

  if (_window == NULL)
  {
    std::cout << "SDL failed to create window! SDL_Error: " << SDL_GetError() << std::endl;
    return;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  _gl_context = SDL_GL_CreateContext(_window);

  gladLoadGLLoader(SDL_GL_GetProcAddress);

  const GLubyte* vendor = glGetString(GL_VENDOR);
  const GLubyte* renderer = glGetString(GL_RENDERER);
  const GLubyte* version = glGetString(GL_VERSION);
  const GLubyte* glsl_version = glGetString(GL_SHADING_LANGUAGE_VERSION);
  const GLubyte* extensions = glGetString(GL_EXTENSIONS);


  _configuration.logger.Log("GL Vendor    : %s \n", vendor);
  _configuration.logger.Log("GL Renderer  : %s \n", renderer);
  _configuration.logger.Log("GL Version   : %s \n", version);
  _configuration.logger.Log("GL Extensions: %s \n", extensions);
  _configuration.logger.Log("GLSL Version : %s \n", glsl_version);

  std::string start_scene("00 - NULL");

  _current_scene_index = _scenes_manager.GetSceneIndex(start_scene);
  _settings_gui.Initialize(_window, _gl_context, _scenes_manager.GetSceneList());
  _settings_gui.SetSceneSelection(_current_scene_index);
  _scenes_manager.SwitchScene(_current_scene_index, &_current_scene);

  _configuration.display.window = _window;
}

void SDLApp::Clean()
{
  _current_scene->Clean();

  _settings_gui.Clean();

  SDL_GL_DeleteContext(_gl_context);
  _gl_context = nullptr;


  SDL_DestroyWindow(_window);
  _window = nullptr;

  SDL_Quit();
}

SDLApp::~SDLApp()
{
}

void SDLApp::ProcessInput()
{
  SDL_Event event;
  while (SDL_PollEvent(&event))
  {
    _settings_gui.ProcessEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
      Quit();
      break;

    default:
      break;
    }
  }

  // Process key without repeat delays
  KeyPress(SDL_GetKeyboardState(NULL));
}

void SDLApp::Update()
{
  _frame_length = 1000 / _configuration.display.framerate;
  float elapsed_time = SDL_GetTicks() - _last_frame_time;
  _last_frame_time = SDL_GetTicks();

  _settings_gui.Update();

  // Check if the scene changed
  SwitchSceneOnSelection();

}

bool SDLApp::IsOver()
{
  return _is_over;
}

void SDLApp::Delay()
{
  int32_t current_frame_length_ = SDL_GetTicks() - _last_frame_time;
  if (_frame_length > current_frame_length_)
  {
    SDL_Delay(_frame_length - current_frame_length_);
  }
}

void SDLApp::Render()
{
  glClearColor(
    _configuration.render.render_clear_color_r,
    _configuration.render.render_clear_color_g,
    _configuration.render.render_clear_color_b,
    1.0f);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _current_scene->Render();
  _settings_gui.Render();
}

void  SDLApp::Quit()
{
  _is_over = true;
}

void SDLApp::KeyPress(const Uint8* key_states)
{
  if (key_states[SDL_SCANCODE_RIGHT])
  {
  }

  if (key_states[SDL_SCANCODE_LEFT])
  {
  }

  if (key_states[SDL_SCANCODE_UP])
  {
  }

  if (key_states[SDL_SCANCODE_DOWN])
  {
  }
}

void SDLApp::SwitchSceneOnSelection()
{
  if (_current_scene_index != _settings_gui.GetSceneSelection())
  {
    _current_scene_index = _settings_gui.GetSceneSelection();
    _scenes_manager.SwitchScene(_current_scene_index, &_current_scene);
  }
}