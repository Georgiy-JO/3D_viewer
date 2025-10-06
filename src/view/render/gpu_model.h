#ifndef SRC_VIEW_RENDER_GUI_MODEL_H
#define SRC_VIEW_RENDER_GUI_MODEL_H
#include <QOpenGLFunctions_3_3_Core>

#include "../../model/model3d/model3d.h"

namespace render {
class GPU_Model : protected QOpenGLFunctions_3_3_Core {
 public:
  GPU_Model();
  ~GPU_Model();

  /**
   * @note Need to have active OpenGL context before calling.
   * @note And call initializeOpenGLFunctions() before calling.
   */
  void InitializeModel();
  void SetModelData(std::shared_ptr<inbound_model::Model3D> model_);
  const GLuint& GetVertexArrayObject() const;
  size_t GetEdgesCount() const;
  size_t GetEdgesAmount() const;
  uint32_t GetVerticesAmount() const;
  const std::string& GetModelName() const;

 private:
  GLuint m_vao;  // Vertex Array Object
  GLuint m_vbo;  // Vertex Buffer Object (vertices)
  GLuint m_ebo;  // Element Buffer Object (edges)

  size_t m_EdgesCount = 0;   // indices in EBO   //it is not edges amount it is
                             // more like count of edges ends
  size_t m_EdgesAmount = 0;  // Amount of edges
  uint32_t m_VerticesAmount = 0;  // indices in VBO
  std::string m_model_name;
};
}  // namespace render

#endif  // SRC_VIEW_RENDER_GUI_MODEL_H