#pragma once
#define Verify()  VerifyImages(__cest_globals.current_test_case->name, OnFailure(__FILE__, __LINE__ - 1))

static inline std::function<void(std::string)> OnFailure(const char *file, int line) {
  return [=](std::string url) {
    throw cest::AssertionError(file, line, "Rendered images do not match. Uploaded image to " + url);
  };
}

void VerifyImages(const std::string& test_case_name, std::function<void(std::string)> on_failure);
