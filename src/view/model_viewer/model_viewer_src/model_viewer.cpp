
#include "../model_viewer.h"

namespace gui {

ModelViewer::ModelViewer(QWidget *parent)
    : QOpenGLWidget(parent), m_render(), m_mouse() {}

void ModelViewer::SetModel(std::shared_ptr<inbound_model::Model3D> model_) {
  m_render.Model().SetModelData(std::move(model_));
  ResetTransformations();
}

void ModelViewer::initializeGL() {
  // initialize function pointers for modern OpenGL (from
  // QOpenGLFunctions_3_3_Core)
  initializeOpenGLFunctions();

  // Basic GL state
  glEnable(GL_DEPTH_TEST);  // enable z-buffer test for correct occlusion

  glEnable(GL_LINE_SMOOTH);  // optional: smoother lines
  // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  // glEnable(GL_MULTISAMPLE);
  glEnable(GL_BLEND);

  m_render.Program().SetVertexShaders();
  m_render.Model().InitializeModel();

  m_render.Camera().Reset();
  glClearColor(service::converters::DoubleToFloat(
                   m_render.Parameters().GetBackgroundColor().x),
               service::converters::DoubleToFloat(
                   m_render.Parameters().GetBackgroundColor().y),
               service::converters::DoubleToFloat(
                   m_render.Parameters().GetBackgroundColor().z),
               service::converters::DoubleToFloat(
                   m_render.Parameters().GetBackgroundColor().w));
}

void ModelViewer::resizeGL(int w, int h) {
  m_render.ResetProjection(w, h);
  glViewport(0, 0, w, h);
}

void ModelViewer::paintGL() {
  try {
    // set background (clear) color
    glClearColor(service::converters::DoubleToFloat(
                     m_render.Parameters().GetBackgroundColor().x),
                 service::converters::DoubleToFloat(
                     m_render.Parameters().GetBackgroundColor().y),
                 service::converters::DoubleToFloat(
                     m_render.Parameters().GetBackgroundColor().z),
                 service::converters::DoubleToFloat(
                     m_render.Parameters().GetBackgroundColor().w));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_render.Model().GetVertexArrayObject() == 0) return;

    // enabling vertice sizing and setting edges width
    glEnable(GL_PROGRAM_POINT_SIZE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(service::converters::DoubleToFloat(
        m_render.Parameters().GetEdgeWidth()));

    // Bind VAO (which also binds VBO/EBO layouts)
    glBindVertexArray(m_render.Model().GetVertexArrayObject());

    if (m_render.Model().GetEdgesCount() != 0 &&
        m_render.Parameters().GetEdgeKind() !=
            controller::Render::EdgeKinds::kNone) {
      m_render.SetEdgeProgram();
      m_render.Program().GetProgram().bind();  // Bind shader program
      // Draw the edges stored in the EBO as lines.
      // GL_LINES: each pair of indices defines a line segment.
      glDrawElements(GL_LINES, m_render.Model().GetEdgesCount(),
                     GL_UNSIGNED_INT, nullptr);
    }
    if (m_render.Parameters().GetVertexKind() !=
        controller::Render::VertexKinds::kNone) {
      m_render.SetVertexProgram();
      m_render.Program().GetProgram().bind();
      glDrawArrays(GL_POINTS, 0, m_render.Model().GetVerticesAmount());
    }

    // Unbind program and VAO
    m_render.Program().GetProgram().release();
    glBindVertexArray(0);
  } catch (const std::exception &e) {
    emit SignalPrintingError(QString("Model printing -> ") + e.what());
  } catch (...) {
    emit SignalPrintingError("Unknown error while printing.");
  }
}

void ModelViewer::mousePressEvent(QMouseEvent *event) {
  m_mouse.PressEvent(event);
  event->accept();
}

void ModelViewer::mouseReleaseEvent(QMouseEvent *event) {
  m_mouse.ReleaseEvent(event);
  event->accept();
}

void ModelViewer::mouseMoveEvent(QMouseEvent *event) {
  auto local_pair = m_mouse.MoveEvent(event);
  RotateY(local_pair.rotation_vec.x);
  RotateX(local_pair.rotation_vec.y);
  Translate(local_pair.translation_vec.x, -local_pair.translation_vec.y, 0);
  event->accept();
  update();
}

void ModelViewer::wheelEvent(QWheelEvent *event) {
  Scale(m_mouse.WheelEvent(event));
  event->accept();
  update();
}

QString ModelViewer::GetModelName() const {
  return QString::fromStdString(m_render.Model().GetModelName());
}

size_t ModelViewer::GetVertsAmount() const {
  return m_render.Model().GetVerticesAmount();
}

size_t ModelViewer::GetEdgesAmount() const {
  return m_render.Model().GetEdgesAmount();
}

void ModelViewer::RotateX(float degrees) {
  m_render.Transform().RotateX(degrees);
}

void ModelViewer::RotateY(float degrees) {
  m_render.Transform().RotateY(degrees);
}

void ModelViewer::RotateZ(float degrees) {
  m_render.Transform().RotateZ(degrees);
}

void ModelViewer::Translate(float x, float y, float z) {
  m_render.Transform().Translate(x, y, z);
}

void ModelViewer::TranslateX(float value) {
  m_render.Transform().Translate(value, 0, 0);
}

void ModelViewer::TranslateY(float value) {
  m_render.Transform().Translate(0, value, 0);
}

void ModelViewer::TranslateZ(float value) {
  m_render.Transform().Translate(0, 0, value);
}

void ModelViewer::Scale(float scale) { m_render.Transform().Scale(scale); }

void ModelViewer::ResetTransformations() { m_render.Transform().Reset(); }

void ModelViewer::SetProjectionKind(const int input) {
  m_render.Parameters().SetProjectionKind(input);
  m_render.ResetProjection(width(), height());
}

int ModelViewer::GetProjectionKind() const {
  return static_cast<int>(m_render.Parameters().GetProjectionKind());
}

void ModelViewer::SetEdgeKind(const int input) {
  m_render.Parameters().SetEdgeKind(input);
}

int ModelViewer::GetEdgeKind() const {
  return static_cast<int>(m_render.Parameters().GetEdgeKind());
}

void ModelViewer::SetVertexKind(const int input) {
  m_render.Parameters().SetVertexKind(input);
}

int ModelViewer::GetVertexKind() const {
  return static_cast<int>(m_render.Parameters().GetVertexKind());
}

void ModelViewer::SetVertexSize(const double input) {
  m_render.Parameters().SetVertexSize(input);
}

double ModelViewer::GetVertexSize() const {
  return m_render.Parameters().GetVertexSize();
}

std::pair<double, double> ModelViewer::GetVertexSizeRange() const {
  return std::pair<double, double>(
      m_render.Parameters().GetVertexSizeRange().min,
      m_render.Parameters().GetVertexSizeRange().max);
}

void ModelViewer::SetEdgeWidth(const double input) {
  m_render.Parameters().SetEdgeWidth(input);
}

double ModelViewer::GetEdgeWidth() const {
  return m_render.Parameters().GetEdgeWidth();
}

std::pair<double, double> ModelViewer::GetEdgeWidthRange() const {
  return std::pair<double, double>(
      m_render.Parameters().GetEdgeWidthRange().min,
      m_render.Parameters().GetEdgeWidthRange().max);
}

void ModelViewer::SetModelColor(QColor input) {
  m_render.Parameters().SetModelColor(vectors::Vec4(
      input.redF(), input.greenF(), input.blueF(), input.alphaF()));
}

QColor ModelViewer::GetModelColor() const {
  return QColor(m_render.Parameters().GetModelColor().x,
                m_render.Parameters().GetModelColor().y,
                m_render.Parameters().GetModelColor().z,
                m_render.Parameters().GetModelColor().w);
}

void ModelViewer::SetBackgroundColor(QColor input) {
  m_render.Parameters().SetBackgroundColor(vectors::Vec4(
      input.redF(), input.greenF(), input.blueF(), input.alphaF()));
}

QColor ModelViewer::GetBackgroundColor() const {
  return QColor(m_render.Parameters().GetBackgroundColor().x,
                m_render.Parameters().GetBackgroundColor().y,
                m_render.Parameters().GetBackgroundColor().z,
                m_render.Parameters().GetBackgroundColor().w);
}

void ModelViewer::ResetParameters() {
  m_render.Parameters().SetDefaults();
  m_render.ResetProjection(width(), height());
}

}  // namespace gui
