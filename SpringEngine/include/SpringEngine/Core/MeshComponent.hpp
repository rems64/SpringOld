#pragma once
#include <SpringEngine/Core/RendereredComponent.hpp>
#include <SpringEngine/Core/Mesh.hpp>
namespace SE
{
	class SE_API MeshComponent : public RenderedComponent
	{
	public:
		MeshComponent(Mesh* instance);
		virtual ~MeshComponent();

		virtual int drawCall() const;

	private:
		Mesh* m_meshInstance;
	};
}