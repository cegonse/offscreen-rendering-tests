#include <cest>
#include "render.h"
#include "verify.h"

describe("Post-processing Camera Shaders", []() {
  it("renders all pixels with bloom effect", []() {
    RenderWithShader("testing-shaders/bloom.fs");
    Verify();
  });

  it("renders all pixels in B&W", []() {
    RenderWithShader("testing-shaders/grayscale.fs");
    Verify();
  });

  afterEach([]() {
    CleanUp();
  });
});
