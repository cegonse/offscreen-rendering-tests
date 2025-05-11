#include "game.h"

int main(int argc, char *argv[])
{
  Game game;
  while (game.ShouldRun()) game.DoFrame();

  return 0;
}
