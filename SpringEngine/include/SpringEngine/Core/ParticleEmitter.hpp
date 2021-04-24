#pragma once

#include <SpringEngine/Core/Vector3.hpp>
#include <SpringEngine/core.hpp>

#include <SpringEngine/Core/DataBlock.hpp>
#include <SpringEngine/Graphics/VertexArray.hpp>
#include <SpringEngine/Graphics/VertexBuffer.hpp>
#include <SpringEngine/Graphics/IndexBuffer.hpp>
#include <SpringEngine/Graphics/VertexBufferLayout.hpp>
#include <SpringEngine/Graphics/Material.hpp>

namespace SE
{
	class ParticleEmitterComponent;
	struct Particle
	{
		Vector3f position;
		float size;
		float age;
		Vector3f velocity;
		float distanceToCam;
		bool operator<(Particle& other) {
			return this->distanceToCam > other.distanceToCam;
		}
	};

	class SE_API ParticleEmitter : public DataBlock
	{
	public:
		ParticleEmitter(ParticleEmitterComponent* owner);
		virtual ~ParticleEmitter();

		void bind();
		void unbind();

		void update(double deltaSeconds);
		void drawCall();

		int getCount() { return m_countParticles; };
		Material* getMaterial() { return m_material.get(); };
		const unsigned int* getIndices() const { return m_vertexBufferIndices; };

	private:
		ParticleEmitterComponent* m_owner;
		static const GLfloat m_vertexBufferData[12];
		static const GLfloat m_vertexBufferUvs[8];
		static const unsigned int m_vertexBufferIndices[6];
		unsigned int m_maxParticles;
		unsigned int m_countParticles;
		
		float* m_particlePositions;
		
		std::shared_ptr<Material> m_material;
		uint32_t m_primitiveBuffer;
		uint32_t m_primitiveUvs;
		uint32_t m_positionsBuffer;
		std::vector<Particle> m_particles;
		Texture* m_texture;
	};
}