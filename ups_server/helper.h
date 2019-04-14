#ifndef __HELPER_H__
#define __HELPER_H__
#include <math.h>
template <typename K, typename P> P getDist(K x1, K y1, K x2, K y2) {
  K diff_x = (x1 - x2);
  K diff_y = (y1 - y2);
  P res = pow(diff_x, 2) + pow(diff_y, 2);
  res = sqrt(res);
  return res;
}
#endif
