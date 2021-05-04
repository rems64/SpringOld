#include <SpringEditor/EditorPropertiesPanel.hpp>
#include <SpringEditor/EditorLayer.hpp>

namespace SpringEditor
{
	EditorLayer* EditorPropertiesPanel::m_editorLayer = nullptr;
	void EditorPropertiesPanel::displayProperties(SE::SceneComponent* component)
	{
		bool translated = SE::ImGuiMisc::coloredVector3Control("Location", component->getLocationRef(), 0.1f, 80.f);
		if (translated)
		{
			component->updateTransform();
		}
		SE::Vector3f rotate = component->getRotation();
		rotate.x(glm::degrees(rotate.x()));
		rotate.y(glm::degrees(rotate.y()));
		rotate.z(glm::degrees(rotate.z()));
		bool rotated = SE::ImGuiMisc::coloredVector3Control("Rotation", rotate, 1.0f, 80.f);
		if (rotated)
		{
			rotate.x(glm::radians(rotate.x()));
			rotate.y(glm::radians(rotate.y()));
			rotate.z(glm::radians(rotate.z()));
			component->getRotationRef() = rotate;
			component->updateTransform();
		}
		bool scaled = SE::ImGuiMisc::coloredVector3Control("Scale", component->getScaleRef(), 0.01f, 80.f);
		if (scaled)
		{
			component->updateTransform();
		}

		ImGui::Dummy(ImVec2(0.0f, 8.0f));

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
					SE::ImGuiMisc::intSelector(property.name.c_str(), (int*)(property.value), property.speed);
					break;
				case SE::EditorPropertyTypes::FloatInput:
					SE::ImGuiMisc::floatSelector(property.name.c_str(), (float*)(property.value), property.speed);
					break;
				case SE::EditorPropertyTypes::BoolInput:
					SE::ImGuiMisc::boolSelector(property.name.c_str(), (bool*)(property.value));
					break;
				case SE::EditorPropertyTypes::ColorInput:
					SE::ImGuiMisc::colorSelector(property.name.c_str(), (SE::Vector3f*)(property.value), property.speed);
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