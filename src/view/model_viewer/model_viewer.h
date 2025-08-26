#ifndef SRC_VIEW_RENDER_MODEL_VIEWER_H
#define SRC_VIEW_RENDER_MODEL_VIEWER_H

#include <QtOpenGLWidgets>
#include "../../core/math/vec4.h"
#include "../../controller/render_controller.h"
#include "mouse_actions.h"

namespace s21::gui{
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
    s21::gui::MouseActions m_mouse;
};

}   //s21::gui








































        

/*
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
    // * @note Called once when the OpenGL context is ready.
    // * @note Used to initialize OpenGL state, load shaders, etc.
    // * @note Automatically called by Qt when QOpenGLWidget is shown for the first time.
     
    void initializeGL() override;  
    // * @note Called when the widget is resized.
    // * @note Sets up the viewport and projection.
    void resizeGL(int w, int h) override;
    // * @note Called every time the widget needs to be redrawn.
    // * @note OpenGL drawing happens here.
    // * @note Usually is used through update().
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
*/
#endif  //SRC_VIEW_RENDER_MODEL_VIEWER_H
