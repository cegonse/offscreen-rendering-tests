#include <string>
extern "C"
{
  #include <wand/MagickWand.h>
}

bool AreImagesDifferent(const std::string& path1, const std::string& path2, double *distortion) {
  MagickWand *img1 = NULL, *img2 = NULL, *diff = NULL;

  MagickWandGenesis();

  img1 = NewMagickWand();
  img2 = NewMagickWand();

  if (MagickReadImage(img1, path1.c_str()) == MagickFalse ||
      MagickReadImage(img2, path2.c_str()) == MagickFalse) {
        if (img1) DestroyMagickWand(img1);
        if (img2) DestroyMagickWand(img2);
        MagickWandTerminus();
        return true;
  }

  if (MagickGetImageWidth(img1) != MagickGetImageWidth(img2) ||
      MagickGetImageHeight(img1) != MagickGetImageHeight(img2)) {
      if (img1) DestroyMagickWand(img1);
      if (img2) DestroyMagickWand(img2);
      MagickWandTerminus();
      return true;
  }

  *distortion = 0.0;
  if (MagickCompareImages(img1, img2, RootMeanSquaredErrorMetric, distortion) == nullptr) {
    if (img1) DestroyMagickWand(img1);
    if (img2) DestroyMagickWand(img2);
    MagickWandTerminus();
    return true;
  }

  return *distortion != 0.0;
}
