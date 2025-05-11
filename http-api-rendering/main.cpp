#include <raylib.h>
#include <render.h>
#include <cstring>

int main(int argc, char *argv[])
{
  if (argc != 4) return 1;

  auto x = std::stof(argv[1]);
  auto y = std::stof(argv[2]);
  auto z = std::stof(argv[3]);

  RenderWithShader("common/bloom.fs", { x, y, z });
  TakeScreenshot("api-out.png");

  CleanUp();
  return 0;
}
