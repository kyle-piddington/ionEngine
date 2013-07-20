#ifndef _ION_SCENE_CDIRECTIONALLIGHTSCENEOBJECT_H_INCLUDED_
#define _ION_SCENE_CDIRECTIONALLIGHTSCENEOBJECT_H_INCLUDED_

#include "ISceneObject.h"
#include "CMeshLoader.h"

/*!
 */
class CDirectionalLightSceneObject : public ISceneObject
{

protected:

	CShader * Shader;
	SColorAf Color;
	SVector3f Direction;

public:

	CDirectionalLightSceneObject(SVector3f const direction, SColorAf const & color = SColorAf(1.f));

	virtual bool draw(IScene const * const scene, smartPtr<IRenderPass> Pass, bool const CullingEnabled);

	virtual void load(IScene const * const Scene, smartPtr<IRenderPass> Pass);

	virtual void setDirection(SVector3f const & direction);
	virtual void setColor(SVector3f const & color);

};

#endif
