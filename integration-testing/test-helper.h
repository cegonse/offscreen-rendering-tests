#pragma once
#include <functional>
#include <map>
#include <string>
#include <raylib.h>
#include <filesystem>
#include <image-compare.h>

#define VerifyFramesSnapshot()  _VerifyFramesSnapshot(OnFailure(__FILE__, __LINE__ - 1))

constexpr int NUM_FRAMES_TO_RENDER = 70;

static inline std::function<void(std::string, double, int)> OnFailure(const char *file, int line) {
  return [=](std::string url, double distortion, int frame) {
    throw cest::AssertionError(file, line, "Rendered images do not match. " + std::to_string(distortion*100.0)  + "% distortion after frame " + std::to_string(frame) + ". Uploaded video to " + url);
  };
}

bool FileExists(const std::string& path_name) {
  return std::filesystem::exists(path_name) && std::filesystem::is_regular_file(path_name);
}

void RemoveFile(const std::string& path_name) {
  std::filesystem::remove(path_name);
}

std::string NewFrameFilename(int frame)
{
  return "integration-testing/snapshots/new_" + std::to_string(frame) + ".png";
}

std::string FrameFilename(int frame)
{
  return "integration-testing/snapshots/" + std::to_string(frame) + ".png";
}

void _VerifyFramesSnapshot(std::function<void(std::string, double, int)> on_failure)
{
  for (int i=0; i<NUM_FRAMES_TO_RENDER; i+=4) {
    if (!FileExists(NewFrameFilename(i))) continue;

    double distortion = 0.0;
    auto difference = AreImagesDifferent(FrameFilename(i), NewFrameFilename(i), &distortion);

    if (difference && distortion > 0.1)
    {
      on_failure("url", distortion, i);
    }
  }

  for (int i=0; i<NUM_FRAMES_TO_RENDER; i+=4) {
    if (!FileExists(NewFrameFilename(i))) continue;
    RemoveFile(NewFrameFilename(i));
  }
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
