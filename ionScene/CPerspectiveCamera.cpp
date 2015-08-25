
#include "CPerspectiveCamera.h"


CPerspectiveCamera::CPerspectiveCamera(ISceneNode * Parent, f32 const aspectRatio, f32 const nearPlane, f32 const farPlane, f32 const focalLength)
	: CCamera(Parent), AspectRatio(aspectRatio), FocalLength(focalLength)
{
	this->NearPlane = nearPlane;
	this->FarPlane = farPlane;
}

void CPerspectiveCamera::RecalculateProjectionMatrix()
{
	ProjectionMatrix = glm::perspective<f32>(GetFieldOfView(), AspectRatio, NearPlane, FarPlane);
}

f32 CPerspectiveCamera::GetFieldOfView() const
{
	return ArcTan(0.5f / FocalLength);
}

f32 CPerspectiveCamera::GetFocalLength() const
{
	return FocalLength;
}

f32 CPerspectiveCamera::GetAspectRatio() const
{
	return AspectRatio;
}

void CPerspectiveCamera::SetFocalLength(f32 const focalLength)
{
	FocalLength = focalLength;
}

void CPerspectiveCamera::SetFieldOfView(f32 const fieldOfView)
{
	FocalLength = 0.5f / Tan(DegreesToRadians(fieldOfView));
}

void CPerspectiveCamera::SetAspectRatio(f32 const aspectRatio)
{
	AspectRatio = aspectRatio;
}
