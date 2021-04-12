#include <SpringEngine/Core/SceneComponent.hpp>

namespace SE
{
	class SE_API RenderedComponent : public SceneComponent
	{
	public:
		RenderedComponent();
		virtual ~RenderedComponent();

		virtual int drawCall() const = 0; // Called by the rendered, return the number of sub-drawcalls

	private:

	};
}