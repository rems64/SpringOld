#pragma once
#include <GL/glew.h>
#include <SpringEngine/Misc/Logger.hpp>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x)\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);