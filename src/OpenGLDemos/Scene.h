#pragma once
#include <SDL.h>
#include "Configurations.h"

class Scene
{
public:
  virtual void Initialize(Subsystems* configuration)
  {
    _configuration = configuration;
  }

  virtual void HandleInput(const Uint8* keybaord_states, int mouse_x, int mouse_y, Uint32 mouse_states) = 0;
  virtual void Update(float delta_time) = 0;
  virtual void Render() = 0;
  virtual void Clean() = 0;

protected:
  Subsystems* _configuration;
};

typedef Scene* (*pfnCreate)(void);