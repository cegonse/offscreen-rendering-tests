#include <raylib.h>
#include <render.h>
#include <charconv>
#include <cstring>

float ParseFloat(char *start)
{
  char *end = std::strchr(start, '\0');
  float result = 0.f;

  const auto [_, success] = std::from_chars(start, end, result);
  if (!(bool)success) return 0.f;

  return result;
}

int main(int argc, char *argv[])
{
  if (argc != 4) return 1;

  auto x = ParseFloat(argv[1]);
  auto y = ParseFloat(argv[2]);
  auto z = ParseFloat(argv[3]);

  RenderWithShader("common/bloom.fs");
  TakeScreenshot("api-out.png");

  CleanUp();
  return 0;
}
