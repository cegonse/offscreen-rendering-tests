#include "platform.h"
#include "platform-test.h"

static bool should_jump = false;

void Platform::ForceJumpKey()
{
  should_jump = true;
}

bool Platform::JumpKeyPressed()
{
  if (should_jump)
  {
    should_jump = false;
    return true;
  }

  return false;
}

float Platform::Random()
{
  return 0.5f;
}
