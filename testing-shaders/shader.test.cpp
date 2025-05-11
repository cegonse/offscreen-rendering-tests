#include <cest>
#include <render.h>
#include "verify.h"

describe("Post-processing Camera Shaders", []() {
  it("renders all pixels with bloom effect", []() {
    RenderWithShader("common/bloom.fs");
    Verify();
  });

  it("renders all pixels in B&W", []() {
    RenderWithShader("common/grayscale.fs");
    Verify();
  });

  afterEach([]() {
    CleanUp();
  });
});
