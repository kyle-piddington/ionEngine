
#pragma once

#include "SVector3.h"


template <typename T, typename Vector = SVector3<T> >
class SLine3
{

	typedef SLine3<T, Vector> Type;

public:

	Vector Start, End;

	SLine3(Vector const & start, Vector const & end)
		: Start(start), End(end)
	{}

	Vector GetMiddle() const
	{
		return (Start + End) / 2;
	}

	Vector GetVector() const
	{
		return Start - End;
	}

	T Length() const
	{
		return GetVector().Length();
	}

	friend T Length(Type const & Line)
	{
		return Line.GetVector().Length();
	}

};

typedef SLine3<f32> SLine3f;
typedef SLine3<f64> SLine3d;
typedef SLine3<s32> SLine3i;

typedef SLine3<f32> line3f;
typedef SLine3<f64> line3d;
typedef SLine3<s32> line3i;
