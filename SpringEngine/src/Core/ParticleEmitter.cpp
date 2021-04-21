#include <SpringEngine/Core/ParticleEmitter.hpp>
#include <SpringEngine/Core/Math.hpp>
#include <SpringEngine/Graphics/Renderer.hpp>
#include <SpringEngine/Graphics/Texture.hpp>
#include <SpringEngine/Core/ParticleEmitterComponent.hpp>
#include <SpringEngine/Core/Actor.hpp>
#include <SpringEngine/Core/Scene.hpp>

namespace SE
{
	extern int randomIntInRange(int min, int max);

	const GLfloat ParticleEmitter::m_vertexBufferData[] = {
			-1.0f, -1.0f,  0.0f,
			 1.0f, -1.0f,  0.0f,
			-1.0f,  1.0f,  0.0f,
			 1.0f,  1.0f,  0.0f
	};

	const GLfloat ParticleEmitter::m_vertexBufferUvs[] = {
		0.0, 0.0,
		1.0, 0.0,
		0.0, 1.0,
		1.0, 1.0
	};

	const GLuint ParticleEmitter::m_vertexBufferIndices[] = {
		0, 1, 2, 1, 2, 3
	};

	ParticleEmitter::ParticleEmitter(ParticleEmitterComponent* owner) : DataBlock(), m_owner(owner), m_maxParticles(100), m_primitiveBuffer(0), m_positionsBuffer(0)
	{
		m_countParticles = 100;
		m_particlePositions = (float*)calloc(m_maxParticles*4, sizeof(float));
		for (unsigned i = 0; i < m_countParticles; i++)
		{
			m_particles.push_back({ SE::Vector3f(randomFloatInRange(-0.5f, 0.5f), randomFloatInRange(-0.5f, 0.5f), randomFloatInRange(-0.5f, 0.5f)), 1.0, 1.0, SE::Vector3f(randomFloatInRange(-0.5f, 0.5f), randomFloatInRange(-0.5f, 0.5f), 0.0)});
			m_particlePositions[3 * i + 0] = m_particles[i].position.x();
			m_particlePositions[3 * i + 1] = m_particles[i].position.y();
			m_particlePositions[3 * i + 2] = m_particles[i].position.z();
		}


		m_material = std::make_shared<Material>("../../../../ISUFlightSimulator/ressources/basic_particle.glsl");
		//m_material->registerProperty(MaterialProperty(SE_MATERIAL_PROPERTY_NAME::DIFFUSE, SE_MATERIAL_PROPERTY_TYPE::COLOR, SE::Vector3f(1.0, 0.2, 0.2)));
		m_texture = new Texture();
		m_texture->loadPNG("../../../../ISUFlightSimulator/ressources/explosion.png", 3, true);
		m_material->registerProperty(MaterialProperty(SE_MATERIAL_PROPERTY_NAME::DIFFUSE, SE_MATERIAL_PROPERTY_TYPE::TEXTURE, m_texture));

		glGenBuffers(1, &m_primitiveBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_primitiveBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertexBufferData), m_vertexBufferData, GL_STATIC_DRAW);

		glGenBuffers(1, &m_primitiveUvs);
		glBindBuffer(GL_ARRAY_BUFFER, m_primitiveUvs);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertexBufferUvs), m_vertexBufferUvs, GL_STATIC_DRAW);

		glGenBuffers(1, &m_positionsBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_positionsBuffer);
		glBufferData(GL_ARRAY_BUFFER, m_maxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
	}

	ParticleEmitter::~ParticleEmitter()
	{

	}

	void ParticleEmitter::bind()
	{
	}

	void ParticleEmitter::unbind()
	{
	}

	void ParticleEmitter::update(double deltaSeconds)
	{
		SE_PROFILE_FUNCTION();
		float rate = 0.001f * deltaSeconds;
		float disparitionRate = 0.0f * deltaSeconds;
		glm::vec3 camPos = m_owner->getActorOwner()->getScene()->getCurrentCamera()->getLocation().getGlm();
		for (unsigned int i=0; i<m_particles.size(); i++)
		{
			m_particles[i].position.x(m_particles[i].position.x() + m_particles[i].velocity.x() * rate);
			m_particles[i].position.y(m_particles[i].position.y() + m_particles[i].velocity.y() * rate);
			m_particles[i].position.z(m_particles[i].position.z());
			m_particles[i].distanceToCam = glm::distance(m_particles[i].position.getGlm(), camPos);
			m_particles[i].size = std::max(0.0f, m_particles[i].size-disparitionRate);
		}
		{
			SE_PROFILE_SCOPE("sorting");
			//std::sort(m_particles.begin(), m_particles.end());
			//bubbleSortVector(m_particles);
		}
		for (unsigned i = 0; i < m_countParticles; i++)
		{
			m_particlePositions[4 * i + 0] = m_particles[i].position.x();
			m_particlePositions[4 * i + 1] = m_particles[i].position.y();
			m_particlePositions[4 * i + 2] = m_particles[i].position.z();
			m_particlePositions[4 * i + 3] = m_particles[i].size;
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_positionsBuffer);
		//glBufferData(GL_ARRAY_BUFFER, m_maxParticles * 3 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, m_countParticles * sizeof(GLfloat) * 4, m_particlePositions);
	}

	void ParticleEmitter::drawCall()
	{
		// Primitive
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_primitiveBuffer);
		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		// UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_primitiveUvs);
		glVertexAttribPointer(
			1,
			2,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		// Positions
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, m_positionsBuffer);
		glVertexAttribPointer(
			2,
			4,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void*)0
		);

		glVertexAttribDivisor(0, 0);
		glVertexAttribDivisor(1, 0);
		glVertexAttribDivisor(2, 1);
		
		// Moved in component
		//m_material->bind();
		//glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, m_countParticles);
		//m_material->unbind();
	}
}