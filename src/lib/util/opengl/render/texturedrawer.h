//
// Created by xukong on 2022/3/11.
//

#pragma once

#include <OpenGL/gl3.h>
#include <QOpenGLFunctions>
#include <memory>
#include "middleware/common/macros.h"
#include "middleware/models/videoframe.h"
#include "shaderprogram.h"
#include "viewport.h"

NAMESPACE_MIDDLEWARE_BEGIN

namespace render::gl {

class TextureDrawer {
   public:
    TextureDrawer(bool isCore = true);
    ~TextureDrawer();
    void drawTexture(const std::shared_ptr<VideoFrame>& frame, const ViewPort& viewPort, bool renderToTexture = false, bool enableInversePremultiplyAlpha = false);

   private:
    std::unique_ptr<ShaderProgram> m_program;
    GLuint m_vao = 0;
    GLuint m_vbos[2] = {0};
};

}  // namespace render::gl
NAMESPACE_MIDDLEWARE_END