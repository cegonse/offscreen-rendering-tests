#include "platform.h"
#include <raylib.h>

bool Platform::JumpKeyPressed()
{
  return IsKeyPressed(KEY_SPACE);
}

float Platform::Random()
{
  return ((float)GetRandomValue(1, 1000) / 1000.f);
}
