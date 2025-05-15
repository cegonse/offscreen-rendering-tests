#include "game.h"

int main(int argc, char *argv[])
{
  auto headless_mode = false;
  Game game(headless_mode);

  while (game.ShouldRun()) game.DoFrame();

  return 0;
}
