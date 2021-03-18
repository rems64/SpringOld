#include <SpringEngine/Core/Layer.hpp>

SE::Layer::Layer(const char* name) : m_name(name), m_enabled(true), m_blockEvents(false)
{
}