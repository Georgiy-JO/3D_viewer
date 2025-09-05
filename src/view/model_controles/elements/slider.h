#ifndef SRC_VIEW_MODEL_CONTROLES_ELEMENTS_SLIDER_H
#define SRC_VIEW_MODEL_CONTROLES_ELEMENTS_SLIDER_H
#include <QSlider>

namespace s21::gui::controles {
class Slider {
 public:
  void Reset(QSlider* slider, const std::pair<int, int> range,
             const int tick_position, const int slide_step);
  /**
   * @return Delta between old and new positions.
   */
  int ResetPosition(int position);

 private:
  int m_position;
};
}  // namespace s21::gui::controles

#endif  // SRC_VIEW_MODEL_CONTROLES_ELEMENTS_SLIDER_H