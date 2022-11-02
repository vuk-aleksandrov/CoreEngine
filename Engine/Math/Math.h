#pragma once

#include <cstdio>
#include <cmath>
#include <algorithm>

#define PI			3.14159265359
#define PI_HALF		1.57079632679
#define PI_QUARTER	0.78539816339

namespace math
{
	struct vec2
	{
		double x = 0, y = 0;
	};

	inline void Sub(const vec2& v1, const vec2& v2, vec2& dest)
	{
		dest = { v1.x - v2.x, v1.y - v2.y };
	}

	struct vec3
	{
		union 
		{
			struct { float x, y, z; };

			float data[3] = {};
		};

		constexpr float& operator[] (int index) 
		{
			return data[index];
		}
	};

	struct vec4
	{
		union
		{
			struct { float x, y, z, w; };

			float data[4] = {};
		};

		constexpr float& operator[] (int index)
		{
			return data[index];
		}
	};

	struct mat3
	{
		vec3 data[3];

		constexpr vec3& operator[] (int index)
		{
			return data[index];
		}
	};

	struct mat4
	{
		vec4 data[4];

		constexpr vec4& operator[] (int index)
		{
			return data[index];
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

	inline void Mul(const vec3& v, float x, vec3& dest)
	{
		dest = { v.x * x, v.y * x, v.z * x };
	}

	inline void Add(const vec3& v1, const vec3& v2, vec3& dest)
	{
		dest = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
	}

	inline void Sub(const vec3& v1, const vec3& v2, vec3& dest)
	{
		dest = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
	}
	
	inline void Add(const vec4& v1, const vec4& v2, vec4& dest)
	{
		dest = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z , 1};
	}

	inline void Sub(const vec4& v1, const vec4& v2, vec4& dest)
	{
		dest = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z , 1};
	}

	inline void Mul(mat3& m, const vec3& v, vec3& dest)
	{
		dest = {
			v.x * m[0].x + v.y * m[1].x + v.z * m[2].x,
			v.x * m[0].y + v.y * m[1].y + v.z * m[2].y,
			v.x * m[0].z + v.y * m[1].z + v.z * m[2].z
		};
	}

	inline void Mul(mat4& m, const vec4& v, vec4& dest)
	{
		dest = {
			v.x * m[0].x + v.y * m[1].x + v.z * m[2].x + v.w * m[3].x,
			v.x * m[0].y + v.y * m[1].y + v.z * m[2].y + v.w * m[3].y,
			v.x * m[0].z + v.y * m[1].z + v.z * m[2].z + v.w * m[3].z,
			v.x * m[0].w + v.y * m[1].w + v.z * m[2].w + v.w * m[3].w
		};
	}

	inline void Mul(mat3& m1, mat3& m2, mat3& dest)
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					dest[i][j] += m1[j][k] * m2[k][i];
				}
			}
		}
	}

	inline void Mul(mat4& m1, mat4& m2, mat4& dest)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					dest[i][j] += m1[j][k] * m2[k][i];
				}
			}
		}
	}

	inline float Length(const vec3& v)
	{
		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	inline void Normalize(vec3& v) {
		const float len = Length(v);
		v.x /= len, v.y /= len, v.z /= len;
	}

	inline float Dot(const vec3& v1, const vec3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	inline void Cross(const vec3& v1, const vec3& v2, vec3& dest)
	{
		dest = {
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		};
	}

	inline void Perspective(mat4& dest, float fov = (float)PI_HALF, float aspect = 1.0f, float zNear = 0.1f, float zFar = 1000.0f)
	{
		dest[1].y = 1.0f / tan(fov / 2.0f);
		dest[0].x = dest[1].y * aspect;
		dest[2].z = -(zFar+zNear) / (zFar - zNear);
		dest[3].z = -2.0f * zNear * zFar / (zFar - zNear);
		dest[2].w = -1;
	}

	inline mat4 InverseView(math::vec3 a, math::vec3 b, math::vec3 c, math::vec3 t)
	{
		return {
			a.x, b.x, c.x, 0,
			a.y, b.y, c.y, 0,
			a.z, b.z, c.z, 0,
			-math::Dot(t, a),
			-math::Dot(t, b),
			-math::Dot(t, c), 1
		};
	}

	inline void RotateAroundX(vec3& v, float theta)
	{
		math::mat3 m;
		m[0].x = 1.f;
		m[1].y = cos(theta);
		m[1].z = -sin(theta);
		m[2].y = -m[1].z;
		m[2].z =  m[1].y;
		Mul(m, v, v);
	}

	inline void RotateAroundY(vec3& v, float theta)
	{
		math::mat3 m;
		m[0].x = cos(theta);
		m[0].z = sin(theta);
		m[1].y = 1;
		m[2].x = -m[0].z;
		m[2].z = m[0].x;
		Mul(m, v, v);
	}

	inline void RotateAroundZ(vec3& v, float theta)
	{
		math::mat3 m;
		m[0].x = cos(theta);
		m[0].y = -sin(theta);
		m[1].x = -m[0].y;
		m[1].y = m[0].x;
		Mul(m, v, v);
	}
}