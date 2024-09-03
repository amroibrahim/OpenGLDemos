#include "ScenesManager.h"

#include "TriangleScene.h"
#include "NullScene.h"

ScenesManager::ScenesManager(Subsystems* configuration)
{
  _subsystems = configuration;
  Register("00 - NULL", &NullScene::Create);
  Register("01 - Triangle", &TriangleScene::Create);
}

std::string ScenesManager::GetSceneList()
{
  std::string list;

  for (std::map <std::string, pfnCreate>::iterator itr = _scene_lookup.begin();
    itr != _scene_lookup.end();
    itr++)
  {
    list += itr->first;
    list.push_back('\0');
  }

  list.push_back('\0');
  return list;
}

void ScenesManager::SwitchScene(int scene_index, Scene** scene)
{
  std::map <std::string, pfnCreate>::iterator itr = _scene_lookup.begin();
  std::advance(itr, scene_index);
  std::string scene_name = itr->first;

  if (*scene != nullptr)
  {
    (*scene)->Clean();
    delete* scene;
  }

  itr = _scene_lookup.find(scene_name);

  if (itr != _scene_lookup.end())
  {
    *scene = itr->second();
  }
  else
  {
    *scene = _scene_lookup.begin()->second();
  }

  (*scene)->Initialize(_subsystems);
}

int ScenesManager::GetSceneIndex(std::string& scene_name)
{
  return distance(_scene_lookup.begin(), _scene_lookup.find(scene_name));
}

void ScenesManager::Register(const std::string& scene_name, pfnCreate create_function)
{
  _scene_lookup[scene_name] = create_function;
}
