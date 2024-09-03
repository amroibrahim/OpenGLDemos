#include "SettingsGUI.h"

SettingsGUI::SettingsGUI(Subsystems* configuration) : _show_log_window(false), _configuration(configuration)
{

}

void SettingsGUI::Initialize(SDL_Window* window, SDL_GLContext gl_context, std::string scenes_list)
{
  _show_log_window = false;
  _window = window;
  _scene_selection = 0;
  _scenes_list = scenes_list;

  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;


  ImGui::StyleColorsDark();
  //ImGui::StyleColorsLight();

  ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
  ImGui_ImplOpenGL3_Init(); 
}

void SettingsGUI::ProcessEvent(SDL_Event* event)
{
  ImGui_ImplSDL2_ProcessEvent(event);
}

void SettingsGUI::Update()
{
  // Start the Dear ImGui frame
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();
}

void SettingsGUI::Render()
{
  // Generate the windows to render
  BuildWindows();

  // Rendering
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  SDL_GL_SwapWindow(_window);
}

void SettingsGUI::BuildWindows()
{
  MainSettingsWindow();

  if (_show_log_window)
  {
    _configuration->logger.Render("Logs");
  }
}

void SettingsGUI::MainSettingsWindow()
{
  ImGui::Begin("Settings");
  ImGui::Text("Display settings");
  ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
  ImGui::SliderFloat("Framerate Limiter", &_configuration->display.framerate, 1.0f, 244.0f);
  ImGui::Checkbox("Logs Window", &_show_log_window);
  ImGui::ColorEdit3("Render Clear", (float*)&_clear_color);
  ImGui::Combo("Scene Selector", &_scene_selection, _scenes_list.c_str());

  _configuration->render.render_clear_color_r = _clear_color.x;
  _configuration->render.render_clear_color_g = _clear_color.y;
  _configuration->render.render_clear_color_b = _clear_color.z;


  ImGui::End();
}

void SettingsGUI::Clean()
{
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
}

void SettingsGUI::SetSceneSelection(int scene_index)
{
  _scene_selection = scene_index;
}

int SettingsGUI::GetSceneSelection()
{
  return _scene_selection;
}
