#pragma once

#include <SpringEngine/core.hpp>
#include <SpringEngine/Core/Vector3.hpp>
#include <SpringEngine/SpringEngine.hpp>

namespace SE
{
	class SE_API ImGuiMisc
	{
	public:
		static bool coloredVector3Control(const char* label, SE::Vector3f& vector, float labelWidth = 80.f, float speed = 0.1f);
		static bool dataBlockSelector(const char* label, SE::DataBlock* datablock, float labelWidth = 80.f);
		static bool intSelector(const char* label, int* value, float labelWidth = 80.f);
		static bool floatSelector(const char* label, float* value, float labelWidth = 80.f);
	};
}

namespace ImGui
{
	// ImGui::InputText() with std::string
	// Because text input needs dynamic resizing, we need to setup a callback to grow the capacity
	SE_API IMGUI_API bool InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
	SE_API IMGUI_API bool InputTextMultiline(const char* label, std::string* str, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
	SE_API IMGUI_API bool InputTextWithHint(const char* label, const char* hint, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
}