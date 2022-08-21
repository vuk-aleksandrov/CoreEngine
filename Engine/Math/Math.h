#pragma once

#include <cstdio>
#include <cmath>

#define pi 3.14159265359

namespace math
{
	struct vec3
	{
		float x, y, z;
	};

	struct vec4
	{
		float x, y, z, w;
	};

	struct mat3
	{
		float data[3 * 3];

		inline float* operator [] (int index)
		{
			return &data[index];
		}

		inline const float* operator [] (int index) const
		{
			return &data[index];
		}
	};

	struct mat4
	{
		float data[4 * 4];

		inline float* operator [] (int index)
		{
			return &data[index];
		}

		inline const float* operator [] (int index) const
		{
			return &data[index];
		}
	};


	inline void Add(const vec3& v, float x, vec3& dest)
	{
		dest.x = v.x + x; dest.y = v.y + x; dest.z = v.z + x;
	}

	inline void Sub(const vec3& v, float x, vec3& dest)
	{
		dest = { v.x - x, dest.y = v.y - x, v.z - x };
	}

	inline void Add(const vec3& v1, const vec3& v2, vec3& dest)
	{
		dest = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
	}

	inline void Sub(const vec3& v1, const vec3& v2, vec3& dest)
	{
		dest = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
	}

	inline void Mul(const mat3& m, const vec3& v, vec3& dest)
	{
		dest = {
			m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z
		};
	}

	inline void Mul(const mat4& m, const vec4& v, vec4& dest)
	{
		dest = {
			m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w,
			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w,
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w,
			m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w
		};
	}

	inline void Mul(const mat3& m1, const mat3& m2, mat3& dest)
	{
		dest = {
			m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0],
			m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1],
			m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2]
		};
	}

	inline void Mul(const mat4& m1, const mat4& m2, mat4& dest)
	{
		dest = {
			m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0], m1[0][3] * m2[3][0],
			m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1], m1[1][3] * m2[3][1],
			m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2], m1[2][3] * m2[3][2],
			m1[3][0] * m2[0][3] + m1[3][1] * m2[1][3] + m1[3][2] * m2[2][3], m1[3][3] * m2[3][3]
		};
	}
}