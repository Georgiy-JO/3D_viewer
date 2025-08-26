#include "model_viewer.h"
// #include <GL/glu.h>     //Needed?

    #include <QMouseEvent>                            // Mouse event types
    #include <QOpenGLShader>                          // For shader type enum
    #include <vector>                                 // std::vector used for staging data
    #include <cstdint>                                // fixed-size integer types



namespace s21::render{


// ModelViewer::ModelViewer(QWidget* parent): QOpenGLWidget(parent), m_model(nullptr){}
ModelViewer::ModelViewer(QWidget* parent): 
    QOpenGLWidget(parent)
    , m_program(this)                               // construct shader program (pass parent for QObject)
{
    // setFocusPolicy so keyboard events are delivered if you want them later
    setFocusPolicy(Qt::StrongFocus);

    // default camera: place camera a bit back along Z so models near origin are visible
    m_view.setToIdentity();                       // start with identity
    m_view.translate(0.0f, 0.0f, -5.0f);           // move camera back 5 units (or move world -5)
}


// Destructor — free GPU resources safely
ModelViewer::~ModelViewer() {
    makeCurrent();               // make sure the GL context is current before deleting GL objects
    deleteBuffers();            // delete VAO/VBO/EBO
    doneCurrent();              // release GL context
}

// Called when user supplies a new model to render
void ModelViewer::SetModel(std::shared_ptr<s21::inbound_model::Model3D> model) {
    m_model = std::move(model); // store the shared_ptr (move if caller used std::move)
    // After storing the model, upload vertex/index data to the GPU
    // We assume this is called from the GUI thread where the GL context is current.
    // If you call SetModel from another thread, ensure it happens on the GUI thread.
    uploadModelToGPU();
    update();                   // schedule a repaint so the new model appears
}

// initializeGL: called once when the GL context is ready
void ModelViewer::initializeGL() {
    // initialize function pointers for modern OpenGL (from QOpenGLFunctions_3_3_Core)
    initializeOpenGLFunctions();

    // Basic GL state
    glEnable(GL_DEPTH_TEST);    // enable z-buffer test for correct occlusion
    glEnable(GL_LINE_SMOOTH);   // optional: smoother lines
    glLineWidth(1.0f);          // default line width (you can tweak later)

    // Initialize our shader program (compile + link)
    initShaders();

    // Create (but do not yet fill) the VAO/VBO/EBO
    createBuffers();

    // If a model was already set before GL init, upload it now
    if (m_model) uploadModelToGPU();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Background color: dark gray, transparency - solid
}

// resizeGL: update projection matrix when the widget size changes
void ModelViewer::resizeGL(int w, int h) {
    // set a perspective projection with 45 deg FOV, near plane 0.1, far 100
    glMatrixMode(GL_PROJECTION); 
    m_projection.setToIdentity();
    m_projection.perspective(45.0f, float(w) / float(h > 0 ? h : 1), 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW); 
}

// paintGL: render the model using our shader program and buffers
void ModelViewer::paintGL() {
    // Clear color and depth buffers
    // glClearColor(0.1f, 0.1f, 0.12f, 1.0f); // dark gray bg
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // If there's no model or no buffers, nothing to draw
    if (!m_model || m_vao == 0 || m_indexCount == 0) return;

    // Bind our shader program so we can set uniforms
    m_program.bind();

    // Build model matrix (scale, rotate, translate)
    QMatrix4x4 model = buildModelMatrix();

    // Upload uniforms (model, view, projection)
    m_program.setUniformValue("model", model);           // model to world
    m_program.setUniformValue("view", m_view);          // world to camera
    m_program.setUniformValue("projection", m_projection); // projection

    // If drawing points and want a program-controlled point size,
    // enable program point size (so gl_PointSize in shader is honored)
    glEnable(GL_PROGRAM_POINT_SIZE);

    // Bind VAO (which also binds VBO/EBO layouts)
    glBindVertexArray(m_vao);

    // Draw the edges stored in the EBO as lines.
    // We're using GL_LINES: each pair of indices defines a line segment.
    glDrawElements(GL_LINES, m_indexCount, GL_UNSIGNED_INT, nullptr);

    // Optionally draw points (vertices) on top; uncomment if you want to also render points.
    // glDrawArrays(GL_POINTS, 0, vertexCount);

    // Unbind VAO and program
    glBindVertexArray(0);
    m_program.release();
}

// mouse events: simple arcball-like rotation by dragging with left button
void ModelViewer::mousePressEvent(QMouseEvent *event) {
    // store the last mouse position for subsequent delta computation
    m_lastMousePos = event->pos();

    // if left button pressed, mark it
    if (event->button() == Qt::LeftButton) m_leftButtonDown = true;
    event->accept();
}

void ModelViewer::mouseMoveEvent(QMouseEvent *event) {
    // compute delta in pixels from last position
    QPoint delta = event->pos() - m_lastMousePos;

    // If left button is down, rotate the model based on mouse movement
    if (m_leftButtonDown) {
        // rotate Y by horizontal movement, X by vertical movement
        m_rotY += delta.x() * 0.5f; // sensitivity factor
        m_rotX += delta.y() * 0.5f;
        update(); // schedule repaint
    }

    // remember last position (for next delta)
    m_lastMousePos = event->pos();
    event->accept();
}

void ModelViewer::wheelEvent(QWheelEvent *event) {
    // Zoom in/out by scaling factor based on wheel delta
    // delta is typically in 1/8 of a degree units; use angleDelta().y()
    int d = event->angleDelta().y();
    if (d != 0) {
        // scale roughly exponentially for nicer feel
        float factor = 1.0f + (d > 0 ? 0.1f : -0.1f);
        m_scale *= factor;
        if (m_scale < 0.01f) m_scale = 0.01f; // clamp min scale
        update();
    }
    event->accept();
}

// --- Helper: initialize shaders (compile & link) ---
// Vertex shader outputs clip-space position. Fragment shader outputs a uniform color.
// You can expand these shaders to include per-vertex color, normals, lighting, etc.
void ModelViewer::initShaders() {
    // Ensure program is empty
    m_program.removeAllShaders();

    // Vertex shader source (GLSL), commented inline for clarity
    const char* vertexSrc = R"(
        #version 330 core                                       // GLSL version
        layout(location = 0) in vec3 aPos;                      // position attribute (vec3)
        uniform mat4 model;                                     // model matrix uniform
        uniform mat4 view;                                      // view (camera) matrix uniform
        uniform mat4 projection;                                // projection matrix uniform
        void main() {
            // compute clip-space position by multiplying matrices
            gl_Position = projection * view * model * vec4(aPos, 1.0);
            // optionally set a constant point size if rendering GL_POINTS
            gl_PointSize = 4.0;
        }
    )";

    // Fragment shader source (GLSL)
    const char* fragmentSrc = R"(
        #version 330 core
        out vec4 FragColor;                                     // final color output
        void main() {
            FragColor = vec4(0.9, 0.8, 0.6, 1.0);               // tan-like color RGBA
        }
    )";

    // Add vertex shader from source string     //can be taken from file btw
    m_program.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexSrc);

    // Add fragment shader from source string     //can be taken from file btw
    m_program.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentSrc);

    // Link the program (throws if link fails; in debug build you can log shader log)
    m_program.link();
}

// --- Helper: create GL buffers (VAO, VBO, EBO) ---
// We create empty buffers here; actual data is uploaded in uploadModelToGPU().
void ModelViewer::createBuffers() {
    // If buffers already exist, delete them first
    deleteBuffers();

    // Generate and bind a Vertex Array Object (VAO)
    glGenVertexArrays(1, &m_vao);          // create 1 VAO and store name in m_vao
    glBindVertexArray(m_vao);              // bind the VAO so subsequent state is stored in it

    // Generate VBO
    glGenBuffers(1, &m_vbo);               // create 1 VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);  // bind VBO as array buffer (vertex data)

    // Define vertex attribute layout matching location=0 in shader:
    // location=0 -> three floats (x,y,z), tightly packed, no stride/offset since only positions.
    glEnableVertexAttribArray(0);          // enable attribute location 0
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Generate EBO (element/index buffer) for edges
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

    // Unbind VAO (safe practice); note: unbinding VAO will keep EBO binding saved inside VAO state
    glBindVertexArray(0);

    // Unbind array buffer to avoid accidental modification later
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// --- Helper: delete GL buffers safely ---
void ModelViewer::deleteBuffers() {
    if (m_ebo) {
        glDeleteBuffers(1, &m_ebo);
        m_ebo = 0;
    }
    if (m_vbo) {
        glDeleteBuffers(1, &m_vbo);
        m_vbo = 0;
    }
    if (m_vao) {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    }
    m_indexCount = 0; // reset index count
}

// --- Helper: convert model data to GPU buffers ---
// This function reads vertices and edges from m_model and uploads them.
// IMPORTANT: adapt the reading code to your Model3D API if names differ.
void ModelViewer::uploadModelToGPU() {
    // If no model, clear buffers and return
    if (!m_model) {
        deleteBuffers();
        return;
    }

    // We'll store positions as float triplets in a std::vector<float>
    std::vector<float> positions;           // x,y,z,x,y,z,...
    std::vector<uint32_t> indices;          // indices for GL_LINES, each pair defines a line

    // === Convert Model3D -> positions + indices ===
    // --- Example A: if Model3D exposes: size_t vertexCount(); Vertex vertexAt(i) with x/y/z; and edges as pairs of ints
    // You'll need to adapt this block to your Model3D's actual API.
    {
        // get vertex count from your model (replace with your actual method)
        const size_t vcount = m_model->GetVerticesAmount(); // <-- adapt this call
        positions.reserve(vcount * 3);                 // reserve storage (3 floats per vertex)

        // iterate vertices and push x,y,z floats
        for (size_t i = 0; i < vcount; ++i) {
            // hypothetical Vertex struct: { float x, y, z; }
            auto v = (*m_model)[i];      // <-- adapt to your Model3D API
            positions.push_back(static_cast<float> (v.x));
            positions.push_back(static_cast<float>(v.y));
            positions.push_back(static_cast<float>(v.z));
        }

        // now edges: assume model has EdgeCount() and EdgeAt(i) returning pair<int,int>
        const size_t ecount = m_model->GetEdgesAmount(); // <-- adapt
        indices.reserve(ecount * 2);                // 2 indices per edge
        for (size_t ei = 0; ei < ecount; ++ei) {
            auto e =( *m_model)(ei);           // <-- adapt: should return {int a, int b}
            indices.push_back(static_cast<uint32_t>(e.begin));
            indices.push_back(static_cast<uint32_t>(e.end));
        }
    }

    // If your Model3D stores other layouts (std::vector of vertices/edges), replace the above block appropriately.
    // The goal: fill 'positions' with floats and 'indices' with uint32 indices indexing positions.

    // === Upload to GL ===
    // Ensure a VAO/VBO/EBO exist
    if (m_vao == 0) createBuffers();  // creates and sets up vertex attribute layout

    // Bind VAO so EBO binding and attribute state apply to this VAO
    glBindVertexArray(m_vao);

    // Bind and upload vertex positions into VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    // Upload data to the GPU buffer. Use STATIC_DRAW for models that don't change frequently.
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float),
                 positions.data(), GL_STATIC_DRAW);

    // Bind and upload element/index data into EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t),
                 indices.data(), GL_STATIC_DRAW);

    // Store index count for draw call (GL wants number of indices)
    m_indexCount = static_cast<GLsizei>(indices.size());

    // Unbind VAO (EBO is part of VAO state, so keep EBO bound when VAO is bound)
    glBindVertexArray(0);

    // Unbind array buffer
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// --- Build model matrix from rotation/translation/scale ---
QMatrix4x4 ModelViewer::buildModelMatrix() const {
    QMatrix4x4 model;
    model.setToIdentity();                     // start with identity matrix

    // Apply translation first (in model space), then rotations, then scale.
    // Order matters: here we do translate -> rotate -> scale, but you can choose desired order.
    model.translate(m_translation);            // move model by translation vector

    // rotate by X, then Y, then Z (degrees)
    model.rotate(m_rotX, 1.0f, 0.0f, 0.0f);
    model.rotate(m_rotY, 0.0f, 1.0f, 0.0f);
    model.rotate(m_rotZ, 0.0f, 0.0f, 1.0f);

    // uniform scale
    model.scale(m_scale);

    return model;
}
















/*

void ModelViewer::SetModel(std::shared_ptr<s21::inbound_model::Model3D> model_ ){
    m_model=std::move(model_);
}

void ModelViewer::initializeGL() {
    initializeOpenGLFunctions();  // Allows access OpenGL functions via Qt
    // Set up OpenGL context
    glEnable(GL_DEPTH_TEST);      // Enables depth testing (objects closer to the camera obscure objects behind them)
    // glEnable(GL_CULL_FACE);       // Optional: Back-face culling (avoids rendering faces that shouldn’t be visible) - not needed in out case
    SetBackgroundColor();
}

void ModelViewer::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);  // Use the full widget
    glMatrixMode(GL_PROJECTION); //tells OpenGL that we’re about to modify the projection matrix (not model).
    SetupProjectionMatrix(w,h);
    glMatrixMode(GL_MODELVIEW);
}

void ModelViewer::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Clears the screen before drawing (colors and depth buffer)
	glMatrixMode(GL_MODELVIEW);
	// glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  // Reset model-view matrix
    SetupCamera();
    SetupAxis();
    if(m_model){
        glColor3f(1.0f, 1.0f, 1.0f);  // Set color: white
        //create a color pallet class and following finctions:white, red, green, blue etc

        glBegin(GL_LINES);  //each pair of glVertex3d will make one line
        size_t amount = m_model->GetEdgesAmount();
        for(size_t i=0; i<amount;i++){ 
            auto& v1 =(*m_model)[(*m_model)(i).begin];
            auto& v2 =(*m_model)[(*m_model)(i).end];
            glVertex3d(v1.x,v1.y,v1.z);  
            glVertex3d(v2.x,v2.y,v2.z);              
        }
        glEnd();    //end for GL_LINES

        
        // // experiment with this shit!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
        // // glEnable(GL_BLEND);
        // // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // // glEnable(GL_POINT_SMOOTH);
        // glPointSize(3);
        // glBegin(GL_POINTS);
        // amount=m_model->GetVerticesAmount();
        // for(size_t i=0; i<amount;i++){
        //     auto& v1=(*m_model)[i];
        //     glVertex3d(v1.x,v1.y,v1.z);
        // }
        // glEnd();    //end for GL_POINTS
        

        // Ok, let's get to rendering and shaders writing. I got rendering function that 
    }
}




// these 4 will probably go to another file (for more info see the header):

void SetupCamera(){
    gluLookAt(1, 1, 3,  // Camera position
              0, 0, 0,  // Look at origin
              0, 1, 0); // Up direction
}

void SetupProjectionMatrix(int w, int h){
    glLoadIdentity();   //resets the projection matrix to default (an identity matrix).
    
    //  * 45.0 — Field of view angle in the Y direction (how "zoomed out" the camera is).
    //  * w/h — Aspect ratio (width divided by height). Prevents distortion when window resizes.
    //  * 0.1 — Near clipping plane: objects closer than this aren't rendered.
    //  * 100.0 — Far clipping plane: objects farther than this aren't rendered.
     
    gluPerspective(45.0, static_cast<double>(w) / h, 0.1, 100.0);
}
void SetBackgroundColor(){
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Background color: dark gray, transparency - solid
}

void SetupAxis(){
    glBegin(GL_LINES);  //replace colors here!!!!!!!!!!!!!!!!!!!!!!
        // X axis (red)
        glColor3f(1, 0, 0);
        glVertex3f(-2, 0, 0);
        glVertex3f(2, 0, 0);

        // Y axis (green)
        glColor3f(0, 1, 0);
        glVertex3f(0, -2, 0);
        glVertex3f(0, 2, 0);

        // Z axis (blue)
        glColor3f(0, 0, 1);
        glVertex3f(0, 0, -2);
        glVertex3f(0, 0, 2);
    glEnd();
}
*/






}   //s21::render