extern "C"
{
  #include <raylib.h>
}
#include <iostream>
#include <sstream>
#include <filesystem>
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

void VerifyImages(const std::string& test_case_name, std::function<void()> on_failure)
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

  if (AreImagesDifferent(saved_file_full, new_file_full)) on_failure();

  RemoveFile(new_file_full);
}
