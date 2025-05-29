#pragma once
#include <functional>
#include <map>
#include <string>
#include <raylib.h>
#include <filesystem>
#include <image-compare.h>
#include <filesystem.h>
#include <constants.h>

#define Verify(fn)  _Verify(fn, OnFailure(__FILE__, __LINE__ - 1))

constexpr int NUM_FRAMES_TO_RENDER = 70;

static inline std::function<void(std::string, std::string)> OnFailure(const char *file, int line) {
  return [=](std::string message, std::string url) {
    throw cest::AssertionError(file, line, message + ". Uploaded video to " + url);
  };
}

std::string NewFrameFilename(int frame)
{
  return "integration-testing/snapshots/new_" + std::to_string(frame) + ".png";
}

std::string FrameFilename(int frame)
{
  return "integration-testing/snapshots/" + std::to_string(frame) + ".png";
}

void CleanUpNewFrames()
{
  for (int i=0; i<NUM_FRAMES_TO_RENDER; i+=HEADLESS_MODE_FRAMESKIP) {
    if (!FileExists(NewFrameFilename(i))) continue;
    RemoveFile(NewFrameFilename(i));
  }
}

void _Verify(std::function<void()> assertion, std::function<void(std::string, std::string)> on_failure)
{
  try
  {
    assertion();
  }
  catch(const cest::AssertionError& e)
  {
    system("./integration-testing/create-video.sh");
    auto url = ReadFile("build/url");
    //RemoveFile("build/url");

    CleanUpNewFrames();
    on_failure(e.message, url);
  }

  CleanUpNewFrames();
}

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
  auto filename = FrameFilename(frame);
  if (FileExists(filename)) filename = NewFrameFilename(frame);

  TakeScreenshot(filename.c_str());
}
