#include "NullScene.h"

void NullScene::Initialize(Subsystems* configuration)
{
  Scene::Initialize(configuration);
}

void NullScene::HandleInput(const Uint8* keybaord_states, int mouse_x, int mouse_y, Uint32 mouse_states)
{
}

void NullScene::Update(float delta_time)
{
}

void NullScene::Render()
{
}

void NullScene::Clean()
{
}
