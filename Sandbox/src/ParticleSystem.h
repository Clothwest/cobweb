#pragma once

#include <Cobweb.h>

struct ParticleProps
{
	glm::vec2 Position;
	glm::vec2 Velocity, VelocityVariation;
	glm::vec4 ColorBegin, ColorEnd;
	float SizeBegin, SizeEnd, SizeVariation;
	float LifeTime;
};

class ParticleSystem
{
public:
	ParticleSystem();

	void OnUpdate(Cobweb::TimeStep ts);
	void OnRender(const Cobweb::OrthographicCamera &camera);

	void Emit(const ParticleProps &particleProps);

private:
	struct Particle
	{
		glm::vec2 Position;
		glm::vec2 Velocity;
		glm::vec4 ColorBegin, ColorEnd;
		float Rotation;
		float SizeBegin, SizeEnd;

		float LifeTime;
		float LifeRemaining;

		bool Active = false;
	};

	std::vector<Particle> m_ParticlePool;
	uint32_t m_PoolIndex = 9999;
};
