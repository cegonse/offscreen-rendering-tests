#include <cest>
#include "game.h"
#include "platform-test.h"
#include "test-helper.h"

describe("JumpingGame", []() {
  it("builds up to 3 points after traversing several columns", []() {
    auto headless_mode = true;
    Game game(headless_mode);

    onEveryNthFrame(6, [](int _) { Platform::ForceJumpKey(); });
    onEveryNthFrame(10, [](int frame) { Screenshot(frame); });
    runFrames(360, [&]() { game.DoFrame(); });

    expect(game.Score()).toBeGreaterThan(3);
  });
});
