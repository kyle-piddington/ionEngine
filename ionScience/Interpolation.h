
#pragma once

template <typename T>
T LinearInterpolate(T y1, T y2, float x)
{
	return y1*(1 - x) + y2*x;
}

template <typename T>
T CubicInterpolate(T p[4], float x)
{
	return p[1] + (T) 0.5 * x*(p[2] - p[0] + x*(2*p[0] - 5*p[1] + 4*p[2] - p[3] + x*(3*(p[1] - p[2]) + p[3] - p[0])));
}

template <typename T>
T BicubicInterpolate(T p[4][4], float x, float y)
{
	T arr[4];
	arr[0] = CubicInterpolate(p[0], y);
	arr[1] = CubicInterpolate(p[1], y);
	arr[2] = CubicInterpolate(p[2], y);
	arr[3] = CubicInterpolate(p[3], y);
	return CubicInterpolate(arr, x);
}

template <typename T>
T TricubicInterpolate(T p[4][4][4], float x, float y, float z)
{
	T arr[4];
	arr[0] = BicubicInterpolate(p[0], y, z);
	arr[1] = BicubicInterpolate(p[1], y, z);
	arr[2] = BicubicInterpolate(p[2], y, z);
	arr[3] = BicubicInterpolate(p[3], y, z);
	return CubicInterpolate(arr, x);
}
