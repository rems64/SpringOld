#include <SpringEngine/UI/ImGuiMisc.hpp>
#include <imgui_internal.h>

namespace SE
{
		bool ImGuiMisc::coloredVector3Control(const char* label, const char* columnId, SE::Vector3f& vector, float& labelWidth, float speed)
		{
			bool modified = false;
			ImGui::PushID(columnId);

			ImGui::Columns(2);
			ImGui::Text(label);
			ImGui::NextColumn();

			ImGui::PopID();
			ImGui::PushID(label);

			ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
			
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f, 0.1f, 0.1f, 1.0f });
			ImGui::Button("");
			ImGui::PopStyleColor();
			ImGui::SameLine();
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, { 0.85f, 0.85f, 0.85f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, { 0.85f, 0.85f, 0.85f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, { 0.85f, 0.85f, 0.85f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_Text, { 0.0f, 0.0f, 0.0f, 1.0f });
			if (ImGui::DragFloat("##X", vector.xPtr(), speed, 0.0f, 0.0f, "%.2f"))
			{
				modified = true;
			}
			ImGui::PopStyleVar(1);
			ImGui::PopStyleColor(4);

			ImGui::PopStyleVar();
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 5, 0 });


			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f, 0.8f, 0.1f, 1.0f });
			ImGui::PopStyleVar();
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
			ImGui::Button("");
			ImGui::PopStyleColor();
			ImGui::SameLine();
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, { 0.85f, 0.85f, 0.85f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, { 0.85f, 0.85f, 0.85f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, { 0.85f, 0.85f, 0.85f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_Text, { 0.0f, 0.0f, 0.0f, 1.0f });
			if(ImGui::DragFloat("##Y", vector.yPtr(), speed, 0.0f, 0.0f, "%.2f"))
			{
				modified = true;
			}
			ImGui::PopStyleVar(1);
			ImGui::PopStyleColor(4);

			ImGui::PopStyleVar();
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 5, 0 });

			ImGui::SameLine();
			ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f, 0.1f, 0.8f, 1.0f });
			ImGui::PopStyleVar();
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });
			ImGui::Button("");
			ImGui::PopStyleColor();
			ImGui::SameLine();
			ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);
			ImGui::PushStyleColor(ImGuiCol_FrameBg, { 0.85f, 0.85f, 0.85f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_FrameBgActive, { 0.85f, 0.85f, 0.85f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, { 0.85f, 0.85f, 0.85f, 1.0f });
			ImGui::PushStyleColor(ImGuiCol_Text, { 0.0f, 0.0f, 0.0f, 1.0f });
			if(ImGui::DragFloat("##Z", vector.zPtr(), speed, 0.0f, 0.0f, "%.2f"))
			{
				modified = true;
			}
			ImGui::PopStyleVar(1);
			ImGui::PopStyleColor(4);
			
			ImGui::PopStyleVar();

			ImGui::Columns(1);
			ImGui::PopID();


			return modified;
		}

		bool ImGuiMisc::dataBlockSelector(const char* label, const char* columnId, SE::DataBlock* datablock, float& labelWidth, float speed)
		{
			ImGui::PushID(label);

			ImGui::BeginColumns("columns3", 2);
			ImGui::Columns(2);
			ImGui::Text(label);
			ImGui::NextColumn();
			ImGui::Text("second");
			ImGui::Columns(1);

			ImGui::PopID();

			return 0;
		}

		bool ImGuiMisc::intSelector(const char* label, const char* columnId, int* value, float& labelWidth, float speed)
		{
			ImGui::PushID(columnId);

			ImGui::Columns(2);
			ImGui::SetColumnWidth(0, labelWidth);
			ImGui::Text(label);
			ImGui::NextColumn();
			ImGui::DragInt(label, value, speed);
			ImGui::Columns(1);

			ImGui::PopID();

			return 0;
		}
		
		bool ImGuiMisc::floatSelector(const char* label, const char* columnId, float* value, float& labelWidth, float speed)
		{
			ImGui::PushID(columnId);

			ImGui::Columns(2);
			ImGui::Text(label);
			ImGui::NextColumn();
			ImGui::DragFloat(label, value, speed);
			ImGui::Columns(1);

			ImGui::PopID();

			return 0;
		}

		bool ImGuiMisc::boolSelector(const char* label, const char* columnId, bool* value, float& labelWidth)
		{
			ImGui::PushID(columnId);

			ImGui::Columns(2);
			ImGui::Text(label);
			ImGui::NextColumn();
			ImGui::Checkbox(label, value);
			ImGui::Columns(1);

			ImGui::PopID();

			return 0;
		}

		bool ImGuiMisc::colorSelector(const char* label, const char* columnId, SE::Vector3f* value, float& labelWidth)
		{
			ImGui::PushID(columnId);

			ImGui::Columns(2);
			ImGui::Text(label);
			ImGui::NextColumn();
			float color[3] = { *value->xPtr(), *value->yPtr(), *value->zPtr() };
			ImGui::ColorEdit3(label, color, ImGuiColorEditFlags_NoInputs);
			value->x(color[0]);
			value->y(color[1]);
			value->z(color[2]);
			ImGui::Columns(1);

			ImGui::PopID();

			return 0;
		}
}


struct InputTextCallback_UserData
{
	std::string* Str;
	ImGuiInputTextCallback  ChainCallback;
	void* ChainCallbackUserData;
};

static int InputTextCallback(ImGuiInputTextCallbackData* data)
{
	InputTextCallback_UserData* user_data = (InputTextCallback_UserData*)data->UserData;
	if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
	{
		// Resize string callback
		// If for some reason we refuse the new length (BufTextLen) and/or capacity (BufSize) we need to set them back to what we want.
		std::string* str = user_data->Str;
		IM_ASSERT(data->Buf == str->c_str());
		str->resize(data->BufTextLen);
		data->Buf = (char*)str->c_str();
	}
	else if (user_data->ChainCallback)
	{
		// Forward to user callback, if any
		data->UserData = user_data->ChainCallbackUserData;
		return user_data->ChainCallback(data);
	}
	return 0;
}

bool ImGui::InputText(const char* label, std::string* str, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
	IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
	flags |= ImGuiInputTextFlags_CallbackResize;

	InputTextCallback_UserData cb_user_data;
	cb_user_data.Str = str;
	cb_user_data.ChainCallback = callback;
	cb_user_data.ChainCallbackUserData = user_data;
	return InputText(label, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallback, &cb_user_data);
}

bool ImGui::InputTextMultiline(const char* label, std::string* str, const ImVec2& size, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
	IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
	flags |= ImGuiInputTextFlags_CallbackResize;

	InputTextCallback_UserData cb_user_data;
	cb_user_data.Str = str;
	cb_user_data.ChainCallback = callback;
	cb_user_data.ChainCallbackUserData = user_data;
	return InputTextMultiline(label, (char*)str->c_str(), str->capacity() + 1, size, flags, InputTextCallback, &cb_user_data);
}

bool ImGui::InputTextWithHint(const char* label, const char* hint, std::string* str, ImGuiInputTextFlags flags, ImGuiInputTextCallback callback, void* user_data)
{
	IM_ASSERT((flags & ImGuiInputTextFlags_CallbackResize) == 0);
	flags |= ImGuiInputTextFlags_CallbackResize;

	InputTextCallback_UserData cb_user_data;
	cb_user_data.Str = str;
	cb_user_data.ChainCallback = callback;
	cb_user_data.ChainCallbackUserData = user_data;
	return InputTextWithHint(label, hint, (char*)str->c_str(), str->capacity() + 1, flags, InputTextCallback, &cb_user_data);
}