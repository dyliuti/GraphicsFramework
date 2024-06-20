#pragma once
#include "glutil.h"
#include <cassert>
#include <memory>

namespace render::gl {
class UTIL_EXPORT TextureLoader : public OpenGLBase {
public:
    using OpenGLBase::OpenGLBase;

    ~TextureLoader();

    template <GLuint type>
    void LoadData2Texture2D(int width, int height, uint8_t* raw_data, int stride)
    {
        uint8_t* data_to_load = nullptr;
        int old_alignment;

        m_gl->glGetIntegerv(GL_UNPACK_ALIGNMENT, &old_alignment);
        m_gl->glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        size_t copy_size = width;

        if (type == GL_LUMINANCE) {
            // align to 4 bytes
            if (width % 4 != 0) {
                copy_size = (width / 4 + 1) * 4;
            }
        } else if (type == GL_RGBA) {
            copy_size = width * 4;
        } else if (type == GL_LUMINANCE_ALPHA) {
            copy_size = width * 2;

            if (width % 2 != 0) {
                copy_size = (width / 2 + 1) * 4;
            }
        }

        if (copy_size == stride) {
            data_to_load = raw_data;
        } else {
            if (!m_buffer || m_bufferLen < copy_size * height) {
                m_buffer.reset(new uint8_t[copy_size * height]);
                m_bufferLen = copy_size * height;
            }

            uint8_t* p = m_buffer.get();
            uint8_t* q = raw_data;

            for (int i = 0; i < height; ++i) {
                memcpy(p, q, copy_size);
                p += copy_size;
                q += stride;
            }

            data_to_load = m_buffer.get();
        }

        m_gl->glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type, GL_UNSIGNED_BYTE, data_to_load);
        m_gl->glPixelStorei(GL_UNPACK_ALIGNMENT, old_alignment);
    }

    template <GLuint type>
    // type is GL_LUMINANCE or GL_RGBA
    GLenum LoadDataToTexture(GLuint tex_id, int width, int height, uint8_t* rawData, int stride)
    {

        m_gl->glBindTexture(GL_TEXTURE_2D, tex_id);
        //        CheckGlError("before LoadData2Texture2D.");
        LoadData2Texture2D<type>(width, height, rawData, stride);
        m_gl->glBindTexture(GL_TEXTURE_2D, 0);
        // CheckGlError("Bind Textures.");
        return GL_NO_ERROR;
    }

private:
    std::unique_ptr<uint8_t[]> m_buffer;
    size_t m_bufferLen = 0;
};
} // namespace render::gl
