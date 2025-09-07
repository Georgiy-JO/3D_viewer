#ifndef SRC_VIEW_CONTROLS_MODEL_CONTROLS_H
#define SRC_VIEW_CONTROLS_MODEL_CONTROLS_H
#include "elements/slider.h"

namespace s21::gui::controls {
class ModelControls {
 public:
  inline void Initialize(QSlider* ox_, QSlider* oy_, QSlider* oz_,
                         QSlider* scale_) {
    m_sl_x.Reset(ox_, kRotateRange, kDefaultRotatePosition, kRotateStep);
    m_sl_y.Reset(oy_, kRotateRange, kDefaultRotatePosition, kRotateStep);
    m_sl_z.Reset(oz_, kRotateRange, kDefaultRotatePosition, kRotateStep);
    m_scale.Reset(scale_, kScaleRange, kDefaultScalePosition, kScaleStep);
    scale_->setVisible(false);
  }
  inline float GetPositiveTranslate() const { return kTranslateStep; }
  inline float GetNegativeTranslate() const { return -kTranslateStep; }
  inline float GetRotateX(int position) {
    return m_sl_x.ResetPosition(position);
  }
  inline float GetRotateY(int position) {
    return m_sl_y.ResetPosition(position);
  }
  inline float GetRotateZ(int position) {
    return m_sl_z.ResetPosition(position);
  }
  inline float GetPositiveScale() const { return kScaleBase + kScaleBigStep; }
  inline float GetNegativeScale() const { return kScaleBase - kScaleBigStep; }

  inline double GetScale(int position) {
    return kScaleBase -
           kScaleStep * static_cast<double>(m_scale.ResetPosition(position));
  }

 private:
  static constexpr std::pair<int, int> kRotateRange{-180, 180};
  static constexpr int kDefaultRotatePosition{0};
  static constexpr int kRotateStep{5};
  static constexpr std::pair<int, int> kScaleRange{-20, 30};
  static constexpr int kDefaultScalePosition{0};
  static constexpr float kScaleBase{1.0f};
  static constexpr float kScaleStep{0.1};
  static constexpr float kScaleBigStep{0.5};
  static constexpr float kTranslateStep{0.5};

  Slider m_sl_x;
  Slider m_sl_y;
  Slider m_sl_z;
  Slider m_scale;
};
}  // namespace s21::gui::controls

#endif  // SRC_VIEW_CONTROLS_MODEL_CONTROLS_H