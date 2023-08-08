#pragma once
#include "ParticleData.h"

namespace kiko
{
	class Particle
	{
	public:
		Particle() = default;
		void Initialize(const ParticleData& data)
		{
			m_data = data;
			m_isActive = true;
		}
		      
		void Update(float dt);
		void Draw(class Renderer& renderer);

		friend class ParticleSystem;
	private:
		ParticleData m_data;
		bool m_isActive = false;
	};
}