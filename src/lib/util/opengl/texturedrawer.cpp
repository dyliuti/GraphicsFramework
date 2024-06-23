#include "texturedrawer.h"
#include "shaderprogram.h"
#include "vertexarrayobject.h"
#include "buffer.h"
#include <QDebug>

namespace render::gl {

//GLfloat vertices[] = {
//    // Positions          // Colors           // Texture Coords
//     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
//     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
//    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
//    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
//};
GLfloat vertices[] = {
    // Positions          // Colors           // Texture Coords
     1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
     1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
    -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
    -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
};
GLuint indices[] = {  // Note that we start from 0!
    0, 1, 3, // First Triangle top right Tri
    1, 2, 3  // Second Triangle bottom left Tri
};

TextureDrawer::TextureDrawer()
    : OpenGLBase()
{
    m_program = std::make_unique<render::gl::ShaderProgram>();
    m_program->createProgram(QString("D:/Work/GraphicsFramework/resource/shader/model.vs"), QString("D:/Work/GraphicsFramework/resource/shader/model.frag"));

    m_vertexArray = std::make_unique<VertexArrayObject>();
    m_vertexArray->bind();

    auto elementBuffer = std::make_shared<ElementBuffer>();
    elementBuffer->bind();
    elementBuffer->write(indices, sizeof(indices));
    auto vertexBuffer = std::make_shared<VertexBuffer>();
    vertexBuffer->bind();
    vertexBuffer->write(vertices, sizeof(vertices));
    // Position attribute
    vertexBuffer->setVertexAttribute(0, 3, 8, 0);
    // Color attribute
    vertexBuffer->setVertexAttribute(1, 3, 8, 3);
    // TexCoord attribute
    vertexBuffer->setVertexAttribute(2, 2, 8, 6);

    m_vertexArray->appendBuffer(elementBuffer);
    m_vertexArray->appendBuffer(vertexBuffer);

    m_vertexArray->release();
}

TextureDrawer::~TextureDrawer()
{

}

void TextureDrawer::drawTexture(GLuint textureId)
{
    // Bind Texture
    m_gl->glActiveTexture(GL_TEXTURE0);
    m_gl->glBindTexture(GL_TEXTURE_2D, textureId);
    m_gl->glUniform1i(m_gl->glGetUniformLocation(m_program->programId(), "ourTexture1"), 0);
    // Activate shader
    m_program->useProgram();
    // draw model
    m_vertexArray->bind();
    m_gl->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    m_vertexArray->release();
}

} // namespace render::gl
