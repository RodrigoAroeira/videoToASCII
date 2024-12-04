#include "resolution.hpp"
#include <algorithm>

Resolution Resolution::operator*(const int val) const {
  return {width / val, height / val};
}

Resolution Resolution::operator/(const int val) const {
  return operator/(1 / val);
}

bool Resolution::operator==(const Resolution &res) const {
  return width == res.width && height == res.height;
}

bool Resolution::operator!=(const Resolution &res) const {
  return !(*this == res);
}

// TODO: Find better scaling method. This one feels weird.
Resolution Resolution::scale(const Resolution &target) {
  float scale_width = target.width / (float)this->width;
  float scale_height = target.height / (float)this->height;
  float scale = std::min(scale_width, scale_height);

  Resolution scaled;

  scaled.width = this->width * scale;
  scaled.height = this->height * scale;

  return scaled;
}
