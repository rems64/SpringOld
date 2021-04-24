#include <SpringEngine/UI/ImGuiMisc.hpp>
#include <imgui_internal.h>

namespace SE
{
		bool ImGuiMisc::coloredVector3Control(const char* label, SE::Vector3f& vector, float labelWidth, float speed)
		{
			bool modified = false;
			ImGui::PushID(label);

			ImGui::Columns(2);
			ImGui::Text(label);
			ImGui::SetColumnWidth(0, labelWidth);
			ImGui::NextColumn();

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

		bool ImGuiMisc::dataBlockSelector(const char* label)
		{
			ImGui::PushID(label);

			ImGui::Image();

			ImGui::PopID();

			return 0;
		}
}