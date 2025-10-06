#include "axisbounds.h"

namespace inbound_model {

AxisBounds& AxisBounds::operator*=(double number) {
  min *= number;
  max *= number;
  return *this;
}

AxisBounds& AxisBounds::operator+=(double number) {
  min += number;
  max += number;
  return *this;
}

void AxisBounds3D::clear() {
  x.min = 0;
  x.max = 0;
  y.min = 0;
  y.max = 0;
  z.min = 0;
  z.max = 0;
}

}  // namespace inbound_model