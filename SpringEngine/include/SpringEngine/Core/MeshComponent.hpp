#pragma once
#include <SpringEngine/Core/RenderedComponent.hpp>
#include <SpringEngine/Core/Mesh.hpp>
#include <SpringEngine/Editor/EditorEditable.hpp>

namespace SE
{
	class ActorComponent;
	SE_CLASS()
	class SE_API MeshComponent : public RenderedComponent, public EditorEditable
	{
	public:
		MeshComponent(ActorComponent* owner, Mesh* instance);
		virtual ~MeshComponent();

		virtual int drawCall() const override;
		Mesh* getInstance() { return m_meshInstance; };
		void setInstance(Mesh* instance) { m_meshInstance = instance; };

		//virtual const char* getPropertyName() override { return "coucou"; };
	protected:
		virtual void onUpdateTransform() override;

	private:
		Mesh* m_meshInstance;
		uint32_t u_subMeshes;
		bool m_debugDrawNormals;
		float m_debugNormalsLength;
	};
}