extern "C"
{
  #include <raylib.h>
}
#include <iostream>
#include <sstream>
#include <filesystem>
#include <fstream>
#include <functional>
#include "image-compare.h"

std::string GenerateVerifierFileName(const std::string& input) {
  std::stringstream ss(input);
  std::string word;
  std::string result;

  while (ss >> word) {
      if (!word.empty()) {
          word[0] = std::toupper(word[0]);
          for (size_t i = 1; i < word.length(); ++i) {
              word[i] = std::tolower(word[i]);
          }
          result += word;
      }
  }

  return result;
}

bool FileExists(const std::string& path_name) {
  return std::filesystem::exists(path_name) && std::filesystem::is_regular_file(path_name);
}

void RemoveFile(const std::string& path_name) {
  std::filesystem::remove(path_name);
}

std::string ReadFile(const std::string& path_name) {
  std::ifstream file(path_name);
  std::stringstream buffer;

  buffer << file.rdbuf();

  return buffer.str();
}

void VerifyImages(const std::string& test_case_name, std::function<void(std::string)> on_failure)
{
  auto saved_file = GenerateVerifierFileName(test_case_name);
  auto new_file = saved_file + "_new";
  auto saved_file_full = saved_file + ".png";
  auto new_file_full = new_file + ".png";

  if (!FileExists(saved_file_full))
  {
    TakeScreenshot(saved_file_full.c_str());
    return;
  }

  TakeScreenshot(new_file_full.c_str());

  double distortion = 0.0;
  if (AreImagesDifferent(saved_file_full, new_file_full, &distortion))
  {
    system("./testing-shaders/upload-imgur.sh");
    auto url = ReadFile("url");
    RemoveFile("url");
    on_failure(url);
  }

  RemoveFile(new_file_full);
}
