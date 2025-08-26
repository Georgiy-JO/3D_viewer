#ifndef SRC_MODEL_RENDER_GUI_MODEL_H
#define SRC_MODEL_RENDER_GUI_MODEL_H
#include <memory>
#include <QOpenGLFunctions_3_3_Core>
#include "../model3d/model3d.h"

namespace s21::render{
class GPU_Model: protected QOpenGLFunctions_3_3_Core {
    public:
        GPU_Model();
        GPU_Model(std::shared_ptr<s21::inbound_model::Model3D> model_);
        ~GPU_Model();

        void SetModelData(std::shared_ptr<s21::inbound_model::Model3D> model_);
        const GLuint& GetVertexArrayObject()const;
        size_t GetEdgesCount() const;
        uint32_t GetVerticesAmount() const;

    private:
        GLuint m_vao;               // Vertex Array Object
        GLuint m_vbo;               // Vertex Buffer Object (vertices)
        GLuint m_ebo;               // Element Buffer Object (edges)

        size_t m_EdgesCount;      //indices in EBO
        uint32_t m_VerticesAmount;   //indices in VBO
        QString m_model_name;
};
}   //s21::render

#endif //SRC_MODEL_RENDER_GUI_MODEL_H