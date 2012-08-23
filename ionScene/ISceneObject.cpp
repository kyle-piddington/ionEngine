#include "ISceneObject.h"


ISceneObject::ISceneObject()
	: DebugDataFlags(0), Visible(true), Parent(0), UseCulling(true), TransformationDirty(false),
	RenderCategory(ERenderCategory::Default)
{}


SBoundingBox3f const & ISceneObject::getAbsoluteBoundingBox() const
{
	return AbsoluteBoundingBox;
}

SBoundingBox3f const & ISceneObject::getBoundingBox() const
{
	return BoundingBox;
}

void ISceneObject::setBoundingBox(SBoundingBox3f const & boundingBox)
{
	BoundingBox = boundingBox;

	BoundingBoxDirty = true;
}


bool const ISceneObject::isDebugDataEnabled(EDebugData const type) const
{
	return (type & DebugDataFlags) != 0;
}

void ISceneObject::enableDebugData(EDebugData const type)
{
	for (std::list<ISceneObject *>::iterator it = Children.begin(); it != Children.end(); ++ it)
		(* it)->enableDebugData(type);

	if (type == EDebugData::All)
		DebugDataFlags = -1;
	else
		DebugDataFlags |= type;
}

void ISceneObject::disableDebugData(EDebugData const type)
{
	for (std::list<ISceneObject *>::iterator it = Children.begin(); it != Children.end(); ++ it)
		(* it)->disableDebugData(type);

	if (type == EDebugData::All)
		DebugDataFlags = 0;
	else
		DebugDataFlags &= ~type;
}


bool const ISceneObject::isVisible() const
{
	return Visible;
}

void ISceneObject::setVisible(bool const isVisible)
{
	// TO DO: Non visible objects should not be a part of hiearchies, so this should trigger a rebuild
	Visible = isVisible;
}

ERenderCategory const ISceneObject::getRenderCategory() const
{
	return RenderCategory;
}

void ISceneObject::setRenderCategory(ERenderCategory const renderCategory)
{
	RenderCategory = renderCategory;
}
