
#include "../model_viewer.h"

namespace s21::gui{

    ModelViewer::ModelViewer(QWidget* parent ):QOpenGLWidget(parent), m_render(), m_mouse(){}

    void ModelViewer::SetModel(std::shared_ptr<s21::inbound_model::Model3D> model_ ){
        m_render.Model().SetModelData(std::move(model_));
        ResetTransformations();
        update();
    }

    void ModelViewer::initializeGL(){
        
        // initialize function pointers for modern OpenGL (from QOpenGLFunctions_3_3_Core)
        initializeOpenGLFunctions();

        // Basic GL state
        glEnable(GL_DEPTH_TEST);    // enable z-buffer test for correct occlusion

        //do I need these?
        glEnable(GL_BLEND);
        glEnable(GL_LINE_SMOOTH);   // optional: smoother lines
        glLineWidth(kLineWidth);
        
        m_render.Program().SetShaders();
        m_render.Model().InitializeModel();

        m_render.Camera().Reset();
        glClearColor(kBackgroundColor.x,kBackgroundColor.y,kBackgroundColor.z,kBackgroundColor.w);  
    }

    void ModelViewer::resizeGL(int w, int h) {
        // glMatrixMode(GL_PROJECTION); 
        m_render.Projection().Reset(w, h);
        glViewport(0, 0, w, h); 
        // glMatrixMode(GL_MODELVIEW); 
    }

    void ModelViewer::paintGL() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(m_render.Model().GetVertexArrayObject()==0 ) return; 

        m_render.SetUniforms();

        // Bind shader program 
        m_render.Program().GetProgram().bind();
        
        glEnable(GL_PROGRAM_POINT_SIZE);
        


        // Bind VAO (which also binds VBO/EBO layouts)
        glBindVertexArray(m_render.Model().GetVertexArrayObject());

        if(m_render.Model().GetEdgesCount()!=0){
            // Draw the edges stored in the EBO as lines.
            // GL_LINES: each pair of indices defines a line segment.
            glDrawElements(GL_LINES, m_render.Model().GetEdgesCount(), GL_UNSIGNED_INT, nullptr);
        }

        glDrawArrays(GL_POINTS, 0, m_render.Model().GetVerticesAmount());

        // Unbind VAO and program
        glBindVertexArray(0);
        m_render.Program().GetProgram().release();
    }

    void ModelViewer::RotateX(float degrees){
        m_render.Transform().RotateX(degrees);
    }

    void ModelViewer::RotateY(float degrees){
        m_render.Transform().RotateY(degrees);
    }

    void ModelViewer::RotateZ(float degrees){
        m_render.Transform().RotateZ(degrees);
    }

    void ModelViewer::Translate(float x, float y, float z){
        m_render.Transform().Translate(x,y,z);
    }

    void ModelViewer::TranslateX(float value){
        m_render.Transform().Translate(value,0,0);
    }

    void ModelViewer::TranslateY(float value){
        m_render.Transform().Translate(0,value,0);
    }
    
    void ModelViewer::TranslateZ(float value){
        m_render.Transform().Translate(0,0,value);
    }

    void ModelViewer::Scale(float scale){
        m_render.Transform().Scale(scale);
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
        Translate(local_pair.translation_vec.x,-local_pair.translation_vec.y,0);
        event->accept();
        update();
    }

    void ModelViewer::wheelEvent(QWheelEvent *event) {
        Scale(m_mouse.WheelEvent(event));
        event->accept();
        update();
    }

    QString ModelViewer::GetModelName() const{
        return QString::fromStdString(m_render.Model().GetModelName());
    }

    size_t ModelViewer::GetVertsAmount() const{
        return m_render.Model().GetVerticesAmount();
    }

    size_t ModelViewer::GetEdgesAmount() const{
        return m_render.Model().GetEdgesAmount();
    }

    void ModelViewer::ResetTransformations(){
        m_render.Transform().Reset();
    }

}   //s21::gui
