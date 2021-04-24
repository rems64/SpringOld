#pragma once

#include <SpringEngine/core.hpp>
#include <SpringEngine/Core/Vector3.hpp>
#include <SpringEngine/SpringEngine.hpp>

namespace SE
{
	class SE_API ImGuiMisc
	{
	public:
		static bool coloredVector3Control(const char* label, SE::Vector3f& vector, float labelWidth = 100.f, float speed = 0.1f);
		static bool dataBlockSelector(const char* label, SE::DataBlock* datablock, float labelWidth=100.f);
	};
}