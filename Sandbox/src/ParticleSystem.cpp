#include "ParticleSystem.h"

#include "Random.h"

ParticleSystem::ParticleSystem()
{
	m_ParticlePool.resize(10000);
}

void ParticleSystem::OnUpdate(Cobweb::TimeStep ts)
{
	for (Particle &p : m_ParticlePool)
	{
		if (!p.Active)
			continue;

		if (p.LifeRemaining <= 0.0f)
		{
			p.Active = false;
			continue;
		}

		p.Position += p.Velocity * ts.GetSeconds();
		p.Rotation += 0.01f * ts.GetSeconds();

		p.LifeRemaining -= ts.GetSeconds();
	}
}

void ParticleSystem::OnRender(const Cobweb::OrthographicCamera &camera)
{
	Cobweb::Renderer2D::BeginScene(camera);

	for (Particle &p : m_ParticlePool)
	{
		if (!p.Active)
			continue;
		
		float life = p.LifeRemaining / p.LifeTime;
		glm::vec4 color = glm::mix(p.ColorEnd, p.ColorBegin, life);
		color.a = glm::mix(0.0f, 1.0f, life);
		float size = glm::mix(p.SizeEnd, p.SizeBegin, life);

		Cobweb::Renderer2D::DrawRotatedQuad(p.Position, { size, size }, p.Rotation, color);
	}

	Cobweb::Renderer2D::EndScene();
}

void ParticleSystem::Emit(const ParticleProps &particleProps)
{
	Particle &particle = m_ParticlePool[m_PoolIndex];
	particle.Active = true;

	particle.Position = particleProps.Position;
	particle.Velocity.x = particleProps.Velocity.x + (Random::Float() - 0.5f) * particleProps.VelocityVariation.x;
	particle.Velocity.y = particleProps.Velocity.y + (Random::Float() - 0.5f) * particleProps.VelocityVariation.y;

	particle.ColorBegin = particleProps.ColorBegin;
	particle.ColorEnd = particleProps.ColorEnd;
	
	particle.Rotation = Random::Float() * 2.0f * glm::pi<float>();

	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;

	particle.SizeBegin = particleProps.SizeBegin + (Random::Float() - 0.5f) * particleProps.SizeVariation;
	particle.SizeEnd = particleProps.SizeEnd;

	m_PoolIndex = m_PoolIndex == 0 ? (uint32_t)m_ParticlePool.size() - 1 : m_PoolIndex - 1;
}
