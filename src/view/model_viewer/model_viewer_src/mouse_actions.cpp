#include "../mouse_actions.h"

namespace s21::gui {
void MouseActions::SetLastMousePosition(QMouseEvent *event) {
  m_lastMousePos.x = event->pos().x();
  m_lastMousePos.y = event->pos().y();
}
void MouseActions::PressEvent(QMouseEvent *event) {
  SetLastMousePosition(event);

  if (event->button() == Qt::LeftButton) m_left_button_down = true;
  if (event->button() == Qt::RightButton) m_right_button_down = true;
}

Vec2Pair MouseActions::MoveEvent(QMouseEvent *event) {
  s21::vectors::Vec2 delta(event->pos().x() - m_lastMousePos.x,
                           event->pos().y() - m_lastMousePos.y);
  Vec2Pair output;

  // If left button is down, rotate the model based on mouse movement
  if (m_left_button_down) {
    output.rotation_vec.x = delta.x * kRotateSensitivityFactor;
    output.rotation_vec.y = delta.y * kRotateSensitivityFactor;
  }
  if (m_right_button_down) {
    output.translation_vec.x = delta.x * kTranslateSensitivityFactor;
    output.translation_vec.y = delta.y * kTranslateSensitivityFactor;
  }

  SetLastMousePosition(event);
  return output;
}

double MouseActions::WheelEvent(QWheelEvent *event) {
  // delta is typically in 1/8 of a degree units
  int d = event->angleDelta().y();
  float factor = 1.0f;
  if (d != 0) {
    // scale roughly exponentially for nicer feel
    factor += (d > 0 ? kScaleSensitivityFactor : -kScaleSensitivityFactor);
    // if (factor < kMinScaleStep) output = kMinScaleStep;
  }
  return factor;
}
void MouseActions::ReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) m_left_button_down = false;
  if (event->button() == Qt::RightButton) m_right_button_down = false;
}
}  // namespace s21::gui
