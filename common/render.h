#pragma once
#include <string>

struct Point {
  float x;
  float y;
  float z;
};

void RenderWithShader(const std::string& path, Point camera_position = {3.f, 3.f, 3.f});

void CleanUp();
