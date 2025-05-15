#pragma once
#include <memory>

class GameState;

class Game
{
  public:
    Game(bool headless_mode);
    ~Game();
    void DoFrame();
    bool ShouldRun();

  private:
    std::unique_ptr<GameState> state;
};
