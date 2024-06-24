#pragma once

#include "glutil.h"
#include "texture.h"

// enum MediaDataType {
//     kMediaDataDefault = 0,
//     kMediaDataVideoBase = 0x20,
//     KMediaDataVideoRGBA,
//     kMediaDataVideoRawGLTexture,
//     kMediaDataEOS = 0x40,
// };

struct Transform {
    int32_t rotation = 0;
    bool mirror = false;
    bool verticalFlip = false;
    uint32_t scaledWidth = 0;
    uint32_t scaledHeight = 0;
    float cropWidthFrac = 1.0;
    float cropHeightFrac = 1.0;
    float cropXFrac = 0;
    float cropYFrac = 0;
};

struct RENDER_EXPORT VideoFrame {
public:
    VideoFrame(std::shared_ptr<render::gl::Texture> tex, uint32_t w, uint32_t h)
        : texture(tex)
        , width(w)
        , height(h)
    {
    }
    Transform transform;
    // unit ms
    uint64_t pts;
    std::shared_ptr<render::gl::Texture> texture;
    uint32_t width;
    uint64_t height;
};
