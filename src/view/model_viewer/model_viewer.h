#ifndef SRC_VIEW_RENDER_MODEL_VIEWER_H
#define SRC_VIEW_RENDER_MODEL_VIEWER_H

#include <QtOpenGLWidgets>

#include "../../controller/render_controller.h"
#include "../../core/math/vec4.h"
#include "mouse_actions.h"

namespace s21::gui {
class ModelViewer : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
  Q_OBJECT

 public:
  explicit ModelViewer(QWidget *parent = nullptr);
  ~ModelViewer() = default;

  void SetModel(std::shared_ptr<s21::inbound_model::Model3D> model_);
  void RotateX(float degrees);
  void RotateY(float degrees);
  void RotateZ(float degrees);
  void Translate(float x, float y, float z);
  void TranslateX(float value);
  void TranslateY(float value);
  void TranslateZ(float value);
  void Scale(float scale);
  void ResetTransformations();

  QString GetModelName() const;
  size_t GetVertsAmount() const;
  size_t GetEdgesAmount() const;

 protected:
  /**
   * @note Called once when the OpenGL context is ready.
   * @note Used to initialize OpenGL state, load shaders, etc.
   * @note Automatically called by Qt when QOpenGLWidget is shown for the first
   * time.
   */
  void initializeGL() override;
  /**
   * @note Called when the widget is resized.
   * @note Sets up the viewport and projection.
   */
  void resizeGL(int w, int h) override;
  /**
   * @note Called every time the widget needs to be redrawn.
   * @note OpenGL drawing happens here.
   * @note Usually is used through update().
   */
  void paintGL() override;

  // Input mouse handling to allow rotation/translation/zoom via mouse/keyboard:
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;

 private:
  s21::controller::Render m_render;
  s21::gui::MouseActions m_mouse;
};

}  // namespace s21::gui

#endif  // SRC_VIEW_RENDER_MODEL_VIEWER_H
