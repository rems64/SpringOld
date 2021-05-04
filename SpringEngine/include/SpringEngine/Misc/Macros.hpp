#pragma once
#include <GL/glew.h>
#include <SpringEngine/Misc/Logger.hpp>

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x)\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);


// NOT WORKING => THROWING RANDOM EXCEPTION
//template <typename T>
//std::string selectRandom(std::initializer_list<T> list)
//{
//    return *(list.begin() + (int)(std::round(((float)std::rand() / RAND_MAX) * (list.size() - 1))) * sizeof(T));
//}


template <typename T>
std::string select(std::initializer_list<T> list, uint32_t index)
{
    return *(list.begin() + index*sizeof(T));
}