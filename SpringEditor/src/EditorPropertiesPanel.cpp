#include <SpringEditor/EditorPropertiesPanel.hpp>
#include <SpringEditor/EditorLayer.hpp>

namespace SpringEditor
{
	EditorLayer* EditorPropertiesPanel::m_editorLayer = nullptr;
	void EditorPropertiesPanel::displayProperties(SE::SceneComponent* component)
	{
		SE::ImGuiMisc::dataBlockSelector("Default", nullptr, 80.f);

		SE::MeshComponent* meshComponent = dynamic_cast<SE::MeshComponent*>(component);
		if (meshComponent)
		{
			SE::Mesh* instance = meshComponent->getInstance();
			if (!instance->isValid())
			{
				if (ImGui::Button("Open from file"))
				{
					m_editorLayer->openModelFromDialogToMeshComponent();
				}
			}
			else
			{
				displayMeshInstanceProperties(instance);
			}
		}
		SE::EditorEditable* editorComponent = dynamic_cast<SE::EditorEditable*>(component);
		if (editorComponent)
		{
			for (SE::EditorProperty property : *editorComponent->getProperties())
			{
				switch (property.type)
				{
				case SE::EditorPropertyTypes::IntInput:
					SE::ImGuiMisc::intSelector(property.name.c_str(), (int*)(property.value));
					break;
				case SE::EditorPropertyTypes::FloatInput:
					SE::ImGuiMisc::floatSelector(property.name.c_str(), (float*)(property.value));
					break;
				default:
					break;

				}
			}
		}
	};

	void EditorPropertiesPanel::displayMeshInstanceProperties(SE::Mesh* mesh)
	{
		//SE::ImGuiMisc::dataBlockSelector("Default");
	}
}