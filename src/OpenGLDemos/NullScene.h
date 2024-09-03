#pragma once
#include "Scene.h"

class NullScene : public Scene
{

public:
  void Initialize(Subsystems* configuration) override;
  void HandleInput(const Uint8* keybaord_states, int mouse_x, int mouse_y, Uint32 mouse_states) override;
  void Update(float delta_time) override;
  void Render() override;
  void Clean() override;

  static Scene* Create() { return new NullScene(); }
};

