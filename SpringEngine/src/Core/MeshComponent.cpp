#include <SpringEngine/Core/MeshComponent.hpp>
#include <SpringEngine/Graphics/Renderer.hpp>

namespace SE
{
	MeshComponent::MeshComponent(Mesh* instance) : m_meshInstance(instance)
	{
	}

	MeshComponent::~MeshComponent()
	{
	}

	int MeshComponent::drawCall() const
	{
		m_meshInstance->getMaterial()->updateShaderUniforms();
		Renderer::drawIndexed(m_meshInstance->getVertexArray(), m_meshInstance->getIndexBuffer(), m_meshInstance->getMaterial(), &m_transform);
		return 1;
	}

	void MeshComponent::onUpdateTransform()
	{
	}
}