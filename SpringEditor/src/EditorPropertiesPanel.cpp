#include <SpringEditor/EditorPropertiesPanel.hpp>
#include <SpringEditor/EditorLayer.hpp>

namespace SpringEditor
{
	EditorLayer* EditorPropertiesPanel::m_editorLayer = nullptr;
	float EditorPropertiesPanel::m_labelsColumnWidth = 80.f;
	void EditorPropertiesPanel::displayProperties(SE::SceneComponent* component)
	{
		bool translated = SE::ImGuiMisc::coloredVector3Control("Location", "propertiesLeftColumn", component->getLocationRef(), m_labelsColumnWidth, 0.1f);
		if (translated)
		{
			component->updateTransform();
		}
		SE::Vector3f rotate = component->getRotation();
		rotate.x(glm::degrees(rotate.x()));
		rotate.y(glm::degrees(rotate.y()));
		rotate.z(glm::degrees(rotate.z()));
		bool rotated = SE::ImGuiMisc::coloredVector3Control("Rotation", "propertiesLeftColumn", rotate, m_labelsColumnWidth, 1.0f);
		if (rotated)
		{
			rotate.x(glm::radians(rotate.x()));
			rotate.y(glm::radians(rotate.y()));
			rotate.z(glm::radians(rotate.z()));
			component->getRotationRef() = rotate;
			component->updateTransform();
		}
		bool scaled = SE::ImGuiMisc::coloredVector3Control("Scale", "propertiesLeftColumn", component->getScaleRef(), m_labelsColumnWidth, 0.01f);
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
				if (!property.shouldDisplay())
				{
					continue;
				}
				switch (property.type)
				{
				case SE::EditorPropertyTypes::IntInput:
					SE::ImGuiMisc::intSelector(property.name.c_str(), "propertiesLeftColumn", (int*)(property.value), m_labelsColumnWidth, property.speed);
					break;
				case SE::EditorPropertyTypes::FloatInput:
					SE::ImGuiMisc::floatSelector(property.name.c_str(), "propertiesLeftColumn", (float*)(property.value), m_labelsColumnWidth, property.speed);
					break;
				case SE::EditorPropertyTypes::BoolInput:
					SE::ImGuiMisc::boolSelector(property.name.c_str(), "propertiesLeftColumn", (bool*)(property.value), m_labelsColumnWidth);
					break;
				case SE::EditorPropertyTypes::ColorInput:
					SE::ImGuiMisc::colorSelector(property.name.c_str(), "propertiesLeftColumn", (SE::Vector3f*)(property.value), m_labelsColumnWidth);
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