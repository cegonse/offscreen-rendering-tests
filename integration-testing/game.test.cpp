#include <cest>
#include "game.h"
#include "platform-test.h"
#include "test-helper.h"

describe("JumpingGame", []() {
  it("builds up to 2 points after traversing several columns", []() {
    auto headless_mode = true;
    Game game(headless_mode);

    onEveryNthFrame(6, [](int _) { Platform::ForceJumpKey(); });
    onEveryNthFrame(4, [](int frame) { Screenshot(frame); });
    runFrames(70, [&]() { game.DoFrame(); });

    expect(game.Score()).toBeGreaterThan(2);
  });
});
