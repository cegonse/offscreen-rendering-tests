#pragma once
#define Verify()  VerifyImages(__cest_globals.current_test_case->name, OnFailure(__FILE__, __LINE__ - 1))

static inline std::function<void()> OnFailure(const char *file, int line) {
  return [=]() {
    throw cest::AssertionError(file, line, "Rendered images do not match");
  };
}

void VerifyImages(const std::string& test_case_name, std::function<void()> on_failure);
