#include "slider.h"

namespace gui::controls {
void Slider::Reset(QSlider* slider, const std::pair<int, int> range,
                   const int tick_position, const int slide_step) {
  slider->setRange(range.first, range.second);
  slider->setValue(tick_position);
  slider->setSingleStep(slide_step);
  m_position = slider->value();
}

int Slider::ResetPosition(int position) {
  int delta = m_position - position;
  m_position = position;
  return delta;
}
}  // namespace gui::controls
