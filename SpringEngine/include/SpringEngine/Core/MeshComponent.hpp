#pragma once
#include <SpringEngine/Core/RenderedComponent.hpp>
#include <SpringEngine/Core/Mesh.hpp>
namespace SE
{
	class ActorComponent;
	class SE_API MeshComponent : public RenderedComponent
	{
	public:
		MeshComponent(ActorComponent* owner, Mesh* instance);
		virtual ~MeshComponent();

		virtual int drawCall() const override;

	protected:
		virtual void onUpdateTransform() override;

	private:
		Mesh* m_meshInstance;
	};
}