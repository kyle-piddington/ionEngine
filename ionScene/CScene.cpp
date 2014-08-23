
#include "CScene.h"


CScene::CScene()
{}

ICamera * const CScene::GetActiveCamera()
{
	return ActiveCamera;
}

ICamera const * const CScene::GetActiveCamera() const
{
	return ActiveCamera;
}

void CScene::SetActiveCamera(ICamera * const activeCamera)
{
	ActiveCamera = activeCamera;
}

void CScene::DrawAll(CDrawManager * Engine)
{
	Engine->Begin(this);

	Root->Update();
	Engine->Update();

	if (Root->IsVisible())
		Engine->Draw(Root->PrepareDrawConfigurations(Engine, DefaultForwardRenderPass));

	Engine->Finalize();
}

ISceneNode * CScene::GetRoot()
{
	return Root;
}
