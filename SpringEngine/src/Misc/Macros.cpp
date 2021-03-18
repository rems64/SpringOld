#include <SpringEngine/Misc/Macros.hpp>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        SE_CORE_ERROR("[OpenGL Error] ({})", error);
        return false;
    }
    return true;
}