#pragma once

#include <cstdio>
#include <cmath>

#define pi			3.14159265359
#define pi_half		1.57079632679
#define pi_quarter	0.78539816339

namespace math
{
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

	inline void Add(const vec3& v1, const vec3& v2, vec3& dest)
	{
		dest = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
	}

	inline void Sub(const vec3& v1, const vec3& v2, vec3& dest)
	{
		dest = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
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

	inline void Perspective(mat4& dest, float fov = (float)pi_half, float aspect = 1.0f, float zNear = 0.1f, float zFar = 1000.0f)
	{
		dest[1].y = 1.0f / tan(fov / 2.0f);
		dest[0].x = dest[1].y * aspect;
		dest[2].z = zFar / (zFar - zNear);
		dest[3].z = -2.0f * zNear * dest[2].z;
		dest[2].w = 1;
	}

	inline void Rotation(mat4& dest, float alpha = 0.0f, float beta = 0.0f, float gamma = 0.0f)
	{
		float sa = sin(alpha), ca = cos(alpha);
		float sb = sin(beta), cb = cos(beta);
		float sc = sin(gamma), cc = cos(gamma);

		dest = {
			ca * cb, ca * sb * sc - sa * cc, ca * sb * cc + sa * sc, 0.f,
			sa * cb, sa * sb * sc + ca * cc, sa * sb * cc - ca * sc, 0.f,
			-sb, cb * sc, cb * cc,0.f,
			0.f, 0.f, 0.f, 1.f
		};
	}

	inline void xRotation(float theta, mat4& dest)
	{
		dest[0].x = 1.f;
		dest[1].y = cos(theta);
		dest[1].z = -sin(theta);
		dest[2].y = -dest[1].z;
		dest[2].z = dest[1].y;
		dest[3].w = 1.0f;
	}

	inline void yRotation(float theta, mat4& dest)
	{
		dest[0].x = cos(theta);
		dest[0].z = sin(theta);
		dest[1].y = 1;
		dest[2].x = -dest[0].z;
		dest[2].z = dest[0].x;
		dest[3].w = 1.0f;
	}

	inline void zRotation(float theta, mat4& dest)
	{
		dest[0].x = cos(theta);
		dest[0].y = -sin(theta);
		dest[1].x = -dest[0].y;
		dest[1].y = dest[0].x;
		dest[3].w = 1.0f;
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
}