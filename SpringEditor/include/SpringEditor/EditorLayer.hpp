#include <SpringEngine/SpringEngine.hpp>

namespace SpringEditor
{
	class EditorLayer : public SE::Layer
	{
	public:
		EditorLayer();

		~EditorLayer();

		virtual void onImGuiRender() override;
	};
}