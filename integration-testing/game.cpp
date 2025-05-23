#include "game.h"
#include "platform.h"
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <raylib.h>

struct GameState {
  Camera2D camera;
  Rectangle player;
  float player_y_speed;
  std::vector<Rectangle> boxes;
  bool dead;
  int score;
  int frame_index;
  bool headless;

  GameState(bool headless_mode) : dead(false), score(0), frame_index(0), headless(headless_mode) {
    camera.target = { 0, 0 };
    camera.offset = { 0, 0 };
    camera.rotation = 0;
    camera.zoom = 1;

    GenerateBoxes();

    player.x = 50;
    player.y = 300-42;
    player.height = 42;
    player.width = 42;
    player_y_speed = 0.f;
  }

  private:

  void GenerateBoxes()
  {
    auto offset = 500.f;
    for (int i = 0; i < 50; ++i) {
      Rectangle first, second;
      first.height = 300;
      first.width = 48;
      first.x = offset + i * 250;
      first.y = 140 * Platform::Random() - 180;

      second.height = first.height;
      second.width = first.width;
      second.x = first.x;
      second.y = first.y + first.height + 200;

      this->boxes.push_back(first);
      this->boxes.push_back(second);
    }
  }
};

void NullLog(int logLevel, const char *text, va_list args) {}

Game::Game(bool headless_mode)
{
  if (headless_mode) SetConfigFlags(FLAG_OFFSCREEN_MODE);
  SetTraceLogCallback(NullLog);
  InitWindow(800, 600, "Game");

  auto target_fps = headless_mode ? 10 : GetMonitorRefreshRate(GetCurrentMonitor());
  SetTargetFPS(target_fps);

  this->state.reset(new GameState(headless_mode));
}

float Game::Score()
{
  return state->score;
}

Game::~Game()
{
  CloseWindow();
}

static void updateState(GameState *state)
{
  if (state->dead) return;

  auto speed = 100.f * GetFrameTime();
  state->camera.target.x += speed;

  state->player_y_speed += 10.f * GetFrameTime();
  state->player.x += speed;
  state->player.y += state->player_y_speed;

  if (Platform::JumpKeyPressed()) state->player_y_speed = -5.f;

  auto player_out_of_vertical_bounds = state->player.y > 650 || state->player.x < -50;
  auto collision = false;
  for (auto box : state->boxes)
    collision |= CheckCollisionRecs(state->player, box);

  if (player_out_of_vertical_bounds || collision) state->dead = true;

  auto distance_target = state->boxes[state->score * 2].x;
  if (state->player.x > distance_target) state->score++;
}

static void render(GameState *state)
{
  auto score_text = std::to_string(state->score);

  BeginDrawing();
  ClearBackground(BLACK);
  BeginMode2D(state->camera);

  bool swap = false;
  for (auto [x, y, width, height] : state->boxes)
  {
    auto startColor = swap ? RED : BLACK;
    auto endColor = swap ? BLACK : RED;
    DrawRectangleGradientV(x, y, width, height, startColor, endColor);
    swap = !swap;
  }

  DrawRectangleRounded(state->player, 0.25, 32, PINK);

  EndMode2D();
  DrawFPS(10, 10);
  DrawText(score_text.c_str(), 390, 10, 60, WHITE);
  EndDrawing();
}

void Game::DoFrame()
{
  auto state = this->state.get();
  state->frame_index++;

  if (state->headless && state->frame_index % 4 == 0)
  {
    render(state);
  }

  updateState(state);
}

bool Game::ShouldRun()
{
  return !WindowShouldClose();
}
