#pragma once

#include <string>

namespace kiko
{
	class Vector3
	{
	public:
		float x, y, z;
	public:
		Vector3() : x{ 0 }, y{ 0 }, z{ 0 } {}
		Vector3(float v) { x = 0; y = 0; z = 0; }
		Vector3(float x, float y, float g) { this->x = x; this->y = y; this->z = z; }
		Vector3(int x, int y, int g) { this->x = (float)x; this->y = (float)y; this->z = (float)g; }

		float operator [] (size_t index) const { return (&x)[index]; }
		float& operator [] (size_t index) { return (&x)[index]; }

		Vector3 operator - () const { return Vector3(-x, -y, -z); }

		Vector3 operator + (const Vector3& v) const { return Vector3(x + v.x, y + v.y, z + v.z); }
		Vector3 operator - (const Vector3& v) const { return Vector3(x - v.x, y - v.y, z - v.z); }
		Vector3 operator / (const Vector3& v) const { return Vector3(x / v.x, y / v.y, z / v.z); }
		Vector3 operator * (const Vector3& v) const { return Vector3(x * v.x, y * v.y, z * v.z); }

		Vector3 operator + (float s) const { return Vector3(x + s, y + s, z + s); }
		Vector3 operator - (float s) const { return Vector3(x - s, y - s, z - s); }
		Vector3 operator / (float s) const { return Vector3(x / s, y / s, z / s); }
		Vector3 operator * (float s) const { return Vector3(x * s, y * s, z * s); }

		Vector3 operator += (const Vector3& v) { x += v.x; y += v.y;  z += v.z; return *this; }
		Vector3 operator -= (const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
		Vector3 operator /= (const Vector3& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }
		Vector3 operator *= (const Vector3& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }

		float LengthSqr() const { return (x * x) + (y * y); }
		float Length() const { return sqrt(LengthSqr()); }

		float DistanceSqr(const Vector3& v) const { return (v - *this).LengthSqr(); }
		float Distance(const Vector3& v) const { return (v - *this).Length(); }

		Vector3 Normalized() const { return *this / Length(); }
		void Normalize() { *this /= Length(); }

		static float Dot(const Vector3& v1, const Vector3& v2);
	};


	inline std::istream& operator >> (std::istream& stream, Vector3& v)
	{
		std::string line;
		std::getline(stream, line);

		// { ##, ## }
		std::string xs = line.substr(line.find("{") + 1, line.find(",") - (line.find("{") + 1));
		v.x = std::stof(xs);

		std::string ys = line.substr(line.find(",") + 1, line.find("}") - (line.find(",") + 1));
		v.y = std::stof(ys);

		return stream;
	}

	inline float Vector3::Dot(const Vector3& v1, const Vector3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	using vec3 = Vector3;
}