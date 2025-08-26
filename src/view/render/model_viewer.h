#ifndef SRC_VIEW_RENDER_MODEL_VIEWER_H
#define SRC_VIEW_RENDER_MODEL_VIEWER_H



#include <QOpenGLFunctions_3_3_Core>
#include "../../model/model3d/model3d.h"
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

#include "../../core/math/matrix4x4.h"
#include <QMatrix4x4>
namespace s21::render::uniforms{

class UniformMatrix{
    public:
        UniformMatrix();
        virtual ~UniformMatrix()=default;

        const s21::matrix::Matrix4x4& GetMatrix() const;
        QMatrix4x4 GetMatrixQT() const;

    protected:
        s21::matrix::Matrix4x4 m_matrix;
};


class TransformationMatrix: public UniformMatrix{
    public:
        TransformationMatrix()=default;

        void Reset();
        void RotateX(float degrees);
        void RotateY(float degrees);
        void RotateZ(float degrees);
        void Translate(float x, float y, float z);
        void Scale(float scale);
};

class CameraMatrix: public UniformMatrix{
    public:
        static constexpr s21::vectors::Vec3 kDefaultCamera {0.0f, 0.0f, -5.0f};
        CameraMatrix();
        void Reset(s21::vectors::Vec3 vec=kDefaultCamera) ;
};

class ProjectionMatrix: public UniformMatrix{
    public:
        static constexpr double kFOVangle = 45.0f; 
        static constexpr double kNearPlane =0.1f; 
        static constexpr double kFarPlane = 100.0f; 
        ProjectionMatrix();
        void Reset(double w, double h, double fov_angle = kFOVangle, double near_plane =kNearPlane, double far_plane =kFarPlane);
};

}       //s21::render::uniforms

#include <QOpenGLShaderProgram>
#include <string>
#include <memory>
namespace s21::render{
class ShaderProgram{
    public:
        static constexpr char* kDefaultVertexShaderPath = "shaders/shader.vert";
        static constexpr char* kDefaultFragmentShaderPath = "shaders/shader.frag";

        void SetShaders();
        void SetShaders(const std::string& vertex_shader_path, const std::string& fragment_shader_path);
        void UploadUniforms(const s21::render::uniforms::TransformationMatrix& trans_marix, 
            const s21::render::uniforms::CameraMatrix& cam_marix, 
            const s21::render::uniforms::ProjectionMatrix& project_matrix);
        void Bind();
        void Unbind();

        QOpenGLShaderProgram& GetProgram();

    private:
        QOpenGLShaderProgram m_program;

};

std::string GetFileData(const std::string& file_name);
}   //s21::render

namespace s21::controller{
class Render{
    public:
        Render():m_model(),m_transformation_matrix(),m_camera_matrix(),m_projection_matrix(),m_program(){}
        Render(std::shared_ptr<s21::inbound_model::Model3D> model_):m_model(model_),m_transformation_matrix(),m_camera_matrix(),m_projection_matrix(),m_program(){}

        s21::render::GPU_Model& Model(){return m_model;}
        s21::render::uniforms::TransformationMatrix& Transform(){return m_transformation_matrix;}
        s21::render::uniforms::CameraMatrix& Camera(){return m_camera_matrix;}
        s21::render::uniforms::ProjectionMatrix& Projection(){return m_projection_matrix;}
        s21::render::ShaderProgram& Program(){return m_program;}
        void SetUniforms(){ 
            m_program.UploadUniforms(m_transformation_matrix,m_camera_matrix,m_projection_matrix);
            m_transformation_matrix.Reset();//????
        }

    private:
        s21::render::GPU_Model m_model;
        s21::render::uniforms::TransformationMatrix m_transformation_matrix;
        s21::render::uniforms::CameraMatrix m_camera_matrix;
        s21::render::uniforms::ProjectionMatrix m_projection_matrix;
        s21::render::ShaderProgram m_program;
};
}   //s21::controller

#include <QMouseEvent>                            // Mouse event types
#include "../../core/math/vec2.h"
namespace s21::gui::openglwidget{
using s21::vectors::Vec2;
struct Vec2Pair{
    Vec2 rotation_vec;
    Vec2 translation_vec;
};

class MouseActions{
    public:
        void PressEvent(QMouseEvent *event) ;
        Vec2Pair MoveEvent(QMouseEvent *event);  // mouse drag -> rotate/translate
        double WheelEvent(QWheelEvent *event);      // wheel -> zoom
        void ReleaseEvent(QMouseEvent *event);

    private:
        static constexpr double kRotateSensitivityFactor=0.5f;
        static constexpr double kTranslateSensitivityFactor=1.0f;
        static constexpr double kScaleSensitivityFactor=0.1f;
        // static constexpr double kMinScaleStep=0.01f;

        void SetLastMousePosition(QMouseEvent *event);
        Vec2 m_lastMousePos;          // last mouse position (used to compute deltas)
        bool m_left_button_down = false;
        bool m_right_button_down = false;
};
}   //s21::gui::openglwidget

#include <QtOpenGLWidgets>
#include "../../core/math/vec4.h"
namespace s21::gui::openglwidget{
class ModelViewer : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core{
 Q_OBJECT

public:
    explicit ModelViewer(QWidget* parent = nullptr);
    ~ModelViewer()=default ;

    void SetModel(std::shared_ptr<s21::inbound_model::Model3D> model_ );
    void RotateX(float degrees);
    void RotateY(float degrees);
    void RotateZ(float degrees);
    void Translate(float x, float y, float z);
    void Scale(float scale);
protected:
    /**
     * @note Called once when the OpenGL context is ready.
     * @note Used to initialize OpenGL state, load shaders, etc.
     * @note Automatically called by Qt when QOpenGLWidget is shown for the first time.
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
    static constexpr s21::vectors::Vec4 kBackgroundColor{0.1f, 0.1f, 0.1f, 1.0f}; // Background color: dark gray, transparency - solid
    static constexpr double kLineWidth = 1.0f;
    s21::controller::Render m_render;
    s21::gui::openglwidget::MouseActions m_mouse;
};

}   //s21::gui::openglwidget








































        


namespace s21::render{
// ModelViewer: QOpenGLWidget that renders a Model3D using shaders and VBO/EBO.
// Inherit QOpenGLFunctions_3_3_Core to access modern GL functions (VAO, VBO, etc.)
class ModelViewer : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
    Q_OBJECT

   public:
    explicit ModelViewer(QWidget* parent = nullptr);
    // Must be called with std::move()

        // Destructor
        ~ModelViewer() override;

    //upload model data to GPU    
    void SetModel(std::shared_ptr<s21::inbound_model::Model3D> model_ );
   protected:
    /**
     * @note Called once when the OpenGL context is ready.
     * @note Used to initialize OpenGL state, load shaders, etc.
     * @note Automatically called by Qt when QOpenGLWidget is shown for the first time.
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


        // Input handling to allow rotation/translation/zoom via mouse/keyboard:
        void mousePressEvent(QMouseEvent *event) override; // start dragging
        void mouseMoveEvent(QMouseEvent *event) override;  // mouse drag -> rotate/translate
        void wheelEvent(QWheelEvent *event) override;      // wheel -> zoom



   private:

   //name of a model would look nice here!!!!!!!!!!!
        // --- GPU objects ---
        QOpenGLShaderProgram m_program; // shader program (vertex + fragment)
        GLuint m_vao = 0;               // Vertex Array Object name/ID
        GLuint m_vbo = 0;               // Vertex Buffer Object name/ID (positions)
        GLuint m_ebo = 0;               // Element Buffer Object name/ID (indices for edges)

        // Count of indices in EBO (so we know how many indices to draw)
        GLsizei m_indexCount = 0;

    // The model stored on CPU-side (the Model3D you provided)
    std::shared_ptr<s21::inbound_model::Model3D> m_model;           //this can be removed

        // Transformation state (model transform: rotation, translation, scale)
        float m_rotX = 0.0f;            // rotation around X axis (degrees)
        float m_rotY = 0.0f;            // rotation around Y axis (degrees)
        float m_rotZ = 0.0f;            // rotation around Z axis (degrees)
        float m_scale = 1.0f;           // uniform scale factor
        QVector3D m_translation = QVector3D(0.0f, 0.0f, 0.0f); // translation vector

        // Camera (view/projection)
        QMatrix4x4 m_view;              // view matrix (camera)
        QMatrix4x4 m_projection;        // projection matrix (perspective)

        // Mouse handling
        QPoint m_lastMousePos;          // last mouse position used to compute deltas
        bool m_leftButtonDown = false;  // whether left mouse button is down

        // Internal helpers
        void initShaders();             // compile and link shaders
        void createBuffers();           // create VAO/VBO/EBO objects (empty)
        void uploadModelToGPU();        // read model on CPU and upload data to VBO/EBO
        void deleteBuffers();           // free GL buffers
        QMatrix4x4 buildModelMatrix() const; // build model matrix from rot/scale/translate
};  


    // // MOVE THIS 4 TO SEPARATE SETUP FUNCTIONS FILE
    // void SetupCamera(); //this function keeps constants in it
    // void SetupProjectionMatrix(int w, int h); //this function keeps constants in it
    // void SetBackgroundColor(); //this function keeps constants in it
    // void SetupAxis();//this function keeps constants in it


}   //s21::render

#endif  //SRC_VIEW_RENDER_MODEL_VIEWER_H
