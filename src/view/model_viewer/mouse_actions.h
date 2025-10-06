#ifndef SRC_VIEW_MODEL_VIEWER_MOUSE_ACTIONS_H
#define SRC_VIEW_MODEL_VIEWER_MOUSE_ACTIONS_H
#include <QMouseEvent>  // Mouse event types

#include "../../core/math/vec2.h"

namespace gui {
struct Vec2Pair {
  vectors::Vec2 rotation_vec;
  vectors::Vec2 translation_vec;
};

class MouseActions {
 public:
  void PressEvent(QMouseEvent *event);
  Vec2Pair MoveEvent(QMouseEvent *event);  // mouse drag -> rotate/translate
  double WheelEvent(QWheelEvent *event);   // wheel -> zoom
  void ReleaseEvent(QMouseEvent *event);

 private:
  static constexpr double kRotateSensitivityFactor = 0.5f;
  static constexpr double kTranslateSensitivityFactor = 0.1f;
  static constexpr double kScaleSensitivityFactor = 0.1f;
  // static constexpr double kMinScaleStep=0.01f;

  void SetLastMousePosition(QMouseEvent *event);
  vectors::Vec2 m_lastMousePos;  // last mouse position (used to compute deltas)
  bool m_left_button_down = false;
  bool m_right_button_down = false;
};
}  // namespace gui

#endif  // SRC_VIEW_MODEL_VIEWER_MOUSE_ACTIONS_H