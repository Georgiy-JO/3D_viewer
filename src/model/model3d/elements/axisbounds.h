#ifndef SRC_MODEL_MODEL3D_ELEMENTS_AXISBOUNDS_H
#define SRC_MODEL_MODEL3D_ELEMENTS_AXISBOUNDS_H

namespace inbound_model {

struct AxisBounds {
  double min = 0;
  double max = 0;

  AxisBounds& operator*=(double number);
  AxisBounds& operator+=(double number);
};

struct AxisBounds3D {
  AxisBounds x;
  AxisBounds y;
  AxisBounds z;

  void clear();
};

}  // namespace inbound_model

#endif  // SRC_MODEL_MODEL3D_ELEMENTS_AXISBOUNDS_H
