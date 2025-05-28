#pragma once
#include <filesystem>
#include <sstream>
#include <fstream>
#include <string>

bool FileExists(const std::string& path_name) {
  return std::filesystem::exists(path_name) && std::filesystem::is_regular_file(path_name);
}

std::string ReadFile(const std::string& path_name) {
  std::ifstream file(path_name);
  std::stringstream buffer;

  buffer << file.rdbuf();

  return buffer.str();
}

void RemoveFile(const std::string& path_name) {
  std::filesystem::remove(path_name);
}
