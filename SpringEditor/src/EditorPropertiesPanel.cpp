#include <SpringEditor/EditorPropertiesPanel.hpp>
#include <SpringEngine/SpringEngine.hpp>
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
			return;
		}
	};

	void EditorPropertiesPanel::displayMeshInstanceProperties(SE::Mesh* mesh)
	{
		//SE::ImGuiMisc::dataBlockSelector("Default");
	}
}