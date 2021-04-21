#include <SpringEngine/Core/MeshComponent.hpp>
#include <SpringEngine/Graphics/Renderer.hpp>

namespace SE
{
	MeshComponent::MeshComponent(ActorComponent* owner, Mesh* instance) : RenderedComponent(owner), m_meshInstance(instance)
	{
		setName(instance->getName());
		m_meshInstance->getMaterial()->updateShaderUniforms();
	}

	MeshComponent::~MeshComponent()
	{
	}

	int MeshComponent::drawCall() const
	{
		Renderer::drawIndexed(m_meshInstance->getVertexArray(), m_meshInstance->getIndexBuffer(), m_meshInstance->getMaterial(), &getTransform());
		return 1;
	}

	void MeshComponent::onUpdateTransform()
	{
	}
}