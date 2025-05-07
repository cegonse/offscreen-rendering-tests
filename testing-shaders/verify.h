#pragma once
#define Verify()  VerifyImages(__cest_globals.current_test_case->name)

void VerifyImages(const std::string& test_case_name);
