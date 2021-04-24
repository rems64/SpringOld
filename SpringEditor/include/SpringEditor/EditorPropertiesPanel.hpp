#pragma once

#include <SpringEngine/SpringEngine.hpp>

namespace SpringEditor
{
	class EditorLayer;
	class EditorPropertiesPanel
	{
	public:
		static void displayProperties(SE::SceneComponent* component);
		static void displayMeshInstanceProperties(SE::Mesh* mesh);
		static void setEditorLayer(EditorLayer* layer) { m_editorLayer = layer; };
	private:
		static EditorLayer* m_editorLayer;
	};
}