#pragma once
#include "Core/Core.h"
#include "Framework/Resource.h"

#include <vector>


namespace kiko
{
	class Renderer;

	class Model : public Resource
	{
	public:
		Model() = default;
		Model(const std::vector<vec2>& points) : m_points{ points } {};


		bool Load(const std::string& filename);
		void Draw(Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(Renderer& renderer, const Transform& transform);

		float GetRadius();
		virtual bool Create(std::string filename, ...) override;

	private:
		std::vector<Vector2> m_points;
		Color m_color;
		float m_radius = 0;

		// Inherited via Resource
	};
}