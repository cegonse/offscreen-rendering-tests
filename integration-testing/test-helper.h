#pragma once
#include <functional>
#include <map>
#include <string>
#include <raylib.h>

struct FrameAction
{
  int frame_count;
  std::function<void(int)> action;
};

static std::vector<FrameAction> frame_actions;

static inline void runFrames(int num_frames, std::function<void()> action)
{
  for (int i=0; i<num_frames; ++i)
  {
    action();

    for (const auto& frame_action : frame_actions)
      if (i % frame_action.frame_count == 0) frame_action.action(i);
  }
}

static inline void onEveryNthFrame(int frame, std::function<void(int)> action)
{
  frame_actions.push_back({ frame, action });
}

void Screenshot(int frame)
{
  auto filename = "integration-testing/snapshots/" + std::to_string(frame) + ".png";
  TakeScreenshot(filename.c_str());
}
