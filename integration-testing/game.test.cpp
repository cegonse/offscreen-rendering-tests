#include <cest>
#include "game.h"
#include "platform-test.h"
#include "test-helper.h"

describe("JumpingGame", []() {
  it("builds up to 5 points after traversing 5 columns", []() {
    auto headless_mode = true;
    Game game(headless_mode);

    onEveryNthFrame(6, [](int _) { Platform::ForceJumpKey(); });
    onEveryNthFrame(10, [](int frame) { Screenshot(frame); });
    runFrames(200, [&]() { game.DoFrame(); });

    expect(game.Score()).toBeGreaterThan(5);
  });
});
