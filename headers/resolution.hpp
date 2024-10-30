#pragma once

#include <opencv2/opencv.hpp>
#include <sys/ioctl.h>
#include <unistd.h>

typedef struct Resolution {
  int width;
  int height;

  Resolution operator/(const int val) const {
    return {width / val, height / val};
  }

  Resolution operator*(const int val) const {
    return {width * val, height * val};
  }

  // TODO: Find better scaling method. This one feels weird.
  Resolution scale(const Resolution &target) {
    float scale_width = target.width / (float)this->width;
    float scale_height = target.height / (float)this->height;
    float scale = std::min(scale_width, scale_height);

    Resolution scaled;

    scaled.width = this->width * scale;
    scaled.height = this->height * scale;

    return scaled;
  }

  bool operator==(const Resolution &res) const {
    return width == res.width && height == res.height;
  }

  bool operator!=(const Resolution &res) const { return !(*this == res); }

} Resolution;
