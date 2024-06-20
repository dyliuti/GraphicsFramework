
#include "glutil.h"

GLenum OpenGlFunction::CheckGlError(const char* message)
{
    GLenum error = GL_NO_ERROR;

    for (GLenum e = glGetError(); e; e = glGetError()) {
        error = e;
        // LOG_ERROR("after {}() glError (0x{:x})\n", message, error);
#if DEBUG
        assert(false);
#endif
    }

    return error;
}
