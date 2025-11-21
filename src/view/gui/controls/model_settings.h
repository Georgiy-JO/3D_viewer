#ifndef SRC_VIEW_GUI_CONTROLS_MODEL_SETTINGS_H
#define SRC_VIEW_GUI_CONTROLS_MODEL_SETTINGS_H
#include <QComboBox>

#include "elements/slider.h"

namespace gui::controls {
class ModelSettings {
 public:
  void InitializeSliders(QSlider* edge_, std::pair<double, double> edge_range,
                         double edge_value, QSlider* vertex_,
                         std::pair<double, double> vertex_range,
                         double vertex_value);
  void InitializeComboBoxes(QComboBox* projection_cbox_,
                            const int projection_cbox_value,
                            QComboBox* edge_cbox_, const int edge_cbox_value,
                            QComboBox* vertex_cbox_,
                            const int vertex_cbox_value);

 private:
  static constexpr int kStepsPerSlide = 20;
  /**
   * @note Folloving constants must be synchronized with enum classes from
   * src/core/parameters/parameters.h
   */
  static constexpr const char* kProjectionKind_0 = "Orthographic Projection";
  static constexpr const char* kProjectionKind_1 = "Central Projection";
  static constexpr const char* kEdgeKind_0 = "No Edges";
  static constexpr const char* kEdgeKind_1 = "Solid Edges";
  static constexpr const char* kEdgeKind_2 = "Dotted Edges";
  static constexpr const char* kVertexKind_0 = "No Vertices";
  static constexpr const char* kVertexKind_1 = "Square Vertices";
  static constexpr const char* kVertexKind_2 = "Circle Vertices";
};

}  // namespace gui::controls

#endif  // SRC_VIEW_GUI_CONTROLS_MODEL_SETTINGS_H