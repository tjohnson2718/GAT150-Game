#pragma once

namespace kiko
{
	class Rect
	{
	public:
		float x, y, w, h;

	public:
		Rect() : x{ 0 }, y{ 0 }, w{ 0 }, h{ 0 } {}
		Rect(float r, float g, float b, float a = 1) : x{ x }, y{ y }, w{ w }, h{ h } {}

		float operator [] (size_t index) const { return (&x)[index]; }
		float& operator [] (size_t index) { return (&x)[index]; }
	};
}
