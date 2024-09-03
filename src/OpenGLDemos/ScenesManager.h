#pragma once
#include <map>
#include <string>

#include "Configurations.h"
#include "Scene.h"

class ScenesManager
{
public:
  ScenesManager(Subsystems* configuration);
  std::string GetSceneList();
  void SwitchScene(int scene_index, Scene** scene);
  int GetSceneIndex(std::string& scene_name);

protected:
  void Register(const std::string& scene_name, pfnCreate create_function);

  std::map <std::string, pfnCreate> _scene_lookup;
  Subsystems* _subsystems;

};

