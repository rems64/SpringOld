#include <SpringEngine/Core/MeshComponent.hpp>
#include <SpringEngine/Graphics/Renderer.hpp>

namespace SE
{
	MeshComponent::MeshComponent(ActorComponent* owner, Mesh* instance) : RenderedComponent(owner), m_meshInstance(instance)
	{
		setName(instance->getName());
		if (m_meshInstance->isValid())
		{
			m_meshInstance->getMaterial()->updateShaderUniforms();
		};

		// Temp workaround
		u_subMeshes = 42;
		addEditorProperty({ SE_EDITOR_PROPERTY_TYPE::MeshAssetInput, "Mesh", (void*)m_meshInstance });
		addEditorProperty({ SE_EDITOR_PROPERTY_TYPE::IntInput, "Sub meshes", (void*)&u_subMeshes });
	}

	MeshComponent::~MeshComponent()
	{
	}

	int MeshComponent::drawCall() const
	{
		if (m_meshInstance->isValid())
		{
			Renderer::drawIndexed(m_meshInstance->getVertexArray(), m_meshInstance->getIndexBuffer(), m_meshInstance->getMaterial(), &getTransform());
			return 1;
		}
		return 0;
	}

	void MeshComponent::onUpdateTransform()
	{
	}
}