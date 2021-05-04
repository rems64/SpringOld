#pragma once

namespace SE
{
	enum class EditorPropertyTypes : uint8_t
	{
		None = 0,
		TextInput,
		IntInput,
		FloatInput,
		BoolInput,
		ColorInput,
		TextureInput,
		MeshAssetInput
	};
	typedef enum EditorPropertyTypes SE_EDITOR_PROPERTY_TYPE;

	struct EditorProperty
	{
		SE_EDITOR_PROPERTY_TYPE type;
		std::string name;
		void* value;
		float speed = 1.0f;
	};
	class EditorEditable
	{
	public:
		virtual ~EditorEditable() {};

		std::vector<EditorProperty>* getProperties() { return &m_editorEditableProperties; };
		void addEditorProperty(EditorProperty property)
		{
			m_editorEditableProperties.emplace_back(property);
		};
	protected:
		std::vector<EditorProperty> m_editorEditableProperties;
	};
}