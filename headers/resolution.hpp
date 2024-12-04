#pragma once

typedef struct Resolution {
  int width;
  int height;

  Resolution operator*(const int val) const;

  Resolution operator/(const int val) const;

  bool operator==(const Resolution &res) const;

  bool operator!=(const Resolution &res) const;

  Resolution scale(const Resolution &target);

} Resolution;
