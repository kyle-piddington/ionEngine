
#pragma once

#include "SVector3.h"


template <typename T>
class STriangle3
{

public:

	SVector3<T> Vertices[3];

	STriangle3()
	{}

	STriangle3(SVector3<T> const & v1, SVector3<T> const & v2, SVector3<T> const & v3)
	{
		Vertices[0] = v1;
		Vertices[1] = v2;
		Vertices[2] = v3;
	}

	bool intersect(SVector3<T> const & p, SVector3<T> const & d)
	{
		SVector3<T> v0, v1, v2;
		v0 = Vertices[0];
		v1 = Vertices[1];
		v2 = Vertices[2];

		SVector3<T> e1, e2, h, s, q;
		T a, f, u, v;
		e1 = v1 - v0;
		e2 = v2 - v0;
		h = Cross(d, e2);
		a = Dot(e1, h);

		if (Equals(a, 0.f))
			return false;

		f = 1 / a;
		s = p - v0;
		u = f * (Dot(s, h));

		if (u < 0.0 || u > 1.0)
			return false;

		q = Cross(s, e1);
		v = f * Dot(d, q);

		if (v < 0.0 || u + v > 1.0)
			return false;

		// at this stage we can compute t to find out where
		// the intersection point is on the line
		f32 t = f * Dot(e2, q);

		if (t > 0.00001) // ray intersection
			return true;

		else // this means that there is a line intersection
			// but not a ray intersection
			return false;
	}

};

typedef STriangle3<f32> STriangle3f;
typedef STriangle3<f64> STriangle3d;
typedef STriangle3<s32> STriangle3i;
typedef STriangle3<u32> STriangle3u;

typedef STriangle3f tri3f;
typedef STriangle3d tri3d;
typedef STriangle3i tri3i;
typedef STriangle3u tri3u;
