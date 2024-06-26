#include "texturedrawer.h"
#include "buffer.h"
#include "shaderprogram.h"
#include "texture.h"
#include "vertexarrayobject.h"
#include <QDebug>
#include <QMatrix4x4>
#include <QMatrix>
namespace render::gl {

// GLfloat vertices[] = {
//     // Positions          // Colors           // Texture Coords
//      0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
//      0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
//     -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
//     -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left
// };
GLfloat vertices[] = {
    // Positions// Colors         // Texture Coords
    1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // Top Right
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
    -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Bottom Left
    -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f // Top Left
};
GLuint indices[] = {
    // Note that we start from 0!
    0, 1, 3, // First Triangle top right Tri
    1, 2, 3 // Second Triangle bottom left Tri
};

TextureDrawer::TextureDrawer()
    : OpenGLBase()
{
    m_program = std::make_unique<render::gl::ShaderProgram>();
    m_program->createProgram(QString(":/common/resource/shader/model.vert"), QString(":/common/resource/shader/model.frag"));

    m_vertexArray = std::make_unique<VertexArrayObject>();
    m_vertexArray->bind();

    auto elementBuffer = std::make_shared<ElementBuffer>();
    elementBuffer->bind();
    elementBuffer->write(indices, sizeof(indices));
    auto vertexBuffer = std::make_shared<VertexBuffer>();
    vertexBuffer->bind();
    vertexBuffer->write(vertices, sizeof(vertices));
    // Position attribute
    vertexBuffer->setVertexAttribute(0, 2, 7, 0);
    // Color attribute
    vertexBuffer->setVertexAttribute(1, 3, 7, 2);
    // TexCoord attribute
    vertexBuffer->setVertexAttribute(2, 2, 7, 5);

    m_vertexArray->appendBuffer(elementBuffer);
    m_vertexArray->appendBuffer(vertexBuffer);

    m_vertexArray->release();
}

TextureDrawer::~TextureDrawer()
{
}

void TextureDrawer::drawTexture(std::shared_ptr<Texture> texture)
{
    m_program->useProgram();
    // Bind Texture
    m_gl->glActiveTexture(GL_TEXTURE0);
    m_gl->glBindTexture(GL_TEXTURE_2D, texture->textureId());
    m_gl->glUniform1i(m_gl->glGetUniformLocation(m_program->programId(), "ourTexture1"), 0);
    m_gl->glUniform2f(m_gl->glGetUniformLocation(m_program->programId(), "iSize"), texture->width(), texture->height());
    // Activate shader

    // draw model
    m_vertexArray->bind();
    m_gl->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    m_vertexArray->release();
}

// void TextureDrawer::setRotateMatrix(const QMatrix2x2& matrix)
//{
//     m_rotateMatrix = matrix;
//     m_gl->glUniformMatrix4fv(m_gl->glGetUniformLocation(m_program->programId(), "rotateMatrix"), 1, GL_FALSE, m_rotateMatrix.constData());
// }

void TextureDrawer::setTime(float time)
{
    m_time = time;
    m_gl->glUniform1f(m_gl->glGetUniformLocation(m_program->programId(), "iTime"), m_time);
}

} // namespace render::gl
