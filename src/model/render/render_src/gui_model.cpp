#include "../gui_model.h"

#include <stdexcept>

namespace s21::render{
GPU_Model::GPU_Model():m_vao(0),m_vbo(0), m_ebo(0), m_EdgesCount(0), m_VerticesAmount(0){}


GPU_Model::~GPU_Model(){
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
    m_EdgesCount = 0;
    m_VerticesAmount=0;
    m_model_name.clear();
}

void GPU_Model::InitializeModel()
{
     // initialize function pointers for modern OpenGL (from QOpenGLFunctions_3_3_Core)
    initializeOpenGLFunctions();


    // Generate and bind a Vertex Array Object (VAO)
    glGenVertexArrays(1, &m_vao);          // create 1 VAO and store name in m_vao
    glBindVertexArray(m_vao);              // bind the VAO so subsequent state is stored in it

    // Generate VBO
    glGenBuffers(1, &m_vbo);               // create 1 VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);  // bind VBO as array buffer (vertex data)

    glEnableVertexAttribArray(0);          // enable attribute location 0
    /**
     * @note Define vertex attribute layout matching location=0:
     *      0 → Attribute location index 0
     *      3 → 3 components (x, y, z) per vertex
     *      GL_FLOAT → Each component is a float
     *      GL_FALSE → Don’t normalize the data
     *      3 * sizeof(float) → Stride = 3 floats per vertex (tightly packed)
     *      (void*)0 → Offset = start at the beginning of the buffer
     */
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Generate EBO (element/index buffer) for edges and tells what kind of buffer it will work with
    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);

    // Unbind VAO (safe practice)
    glBindVertexArray(0);

    // Unbind array buffer to avoid accidental modification later
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void GPU_Model::SetModelData(std::shared_ptr<s21::inbound_model::Model3D> model_){
    // Ensure a VAO/VBO/EBO exist
    if (m_vao == 0)
        throw std::runtime_error("GPU buffers were not initialized (something went terribly wrong).");
        
    if (!model_ || model_->GetVerticesAmount()==0) 
        throw std::invalid_argument("Model is empty or null");

    m_VerticesAmount = model_->GetVerticesAmount();
    m_EdgesCount=model_->GetEdgesAmount();     //it is not actually edges amount it is more like count of edges ends
    m_model_name=QString::fromStdString(model_->GetName());

    /**
     * @note We need do transfor the data from Model3D to save space and store data tightly.
     *      We could send Vec3 straight to GPU if Vec3 would be based of float (it's double).
     *      Overflow won't happen due to fact that model is normalized already.
     */
    std::vector<float> vertices;           // will store in form: x,y,z,x,y,z,...
    vertices.reserve(m_VerticesAmount * 3);
    s21::vectors::Vec3 v;
    for (uint32_t i = 0; i < m_VerticesAmount; ++i) {
        v = static_cast<s21::vectors::Vec3>((*model_)[i]);
        if(v.x>std::numeric_limits<float>::max() || v.y>std::numeric_limits<float>::max()|| v.z>std::numeric_limits<float>::max())
            throw std::runtime_error("Model was not normalized before passing to GPU buffer (Vertex has value out of range).");
        vertices.push_back(static_cast<float> (v.x));
        vertices.push_back(static_cast<float>(v.y));
        vertices.push_back(static_cast<float>(v.z));
    }

    std::vector<uint32_t> edges;
    edges.reserve(m_EdgesCount*2);
    s21::inbound_model::Edge e(0,0);
    for (size_t i = 0; i < m_EdgesCount; ++i){
        e=static_cast<s21::inbound_model::Edge>((*model_)(i));
        edges.push_back(e.begin);
        edges.push_back(e.end);
    }
    m_EdgesCount*=2;
  
    // Bind VAO so EBO binding and attribute state apply to this VAO
    glBindVertexArray(m_vao);

    // Bind and upload vertex positions into VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    /**
     * @note Upload data to the GPU buffer. 
     *      GL_ARRAY_BUFFER - it tells OpenGL that the buffer we’re working with is a vertex attribute 
     *      buffer (it is connected to m_vbo).
     *      GL_STATIC_DRAW - it tells OpenGL that we won’t be modifying the data in the buffer very often
     *      (GL_STREAM_DRAW → changes every frame). We are using GPU side transformations (via shaders): 
     *      in this case the vertex buffer data stays the same — the GPU just transforms it on the fly for rendering.
    */
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float),
                 vertices.data(), GL_STATIC_DRAW);

    // Bind and upload element/index data into EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, edges.size() * sizeof(uint32_t),
                 edges.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

const GLuint& GPU_Model::GetVertexArrayObject()const{
    return m_vao;
}

size_t GPU_Model::GetEdgesCount() const{
    return m_EdgesCount;
}

uint32_t GPU_Model::GetVerticesAmount() const{
    return m_VerticesAmount;
}
}   //s21::render