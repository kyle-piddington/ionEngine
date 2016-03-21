
#pragma once

#include "ICamera.h"
#include "ILight.h"
#include "ISceneObject.h"


namespace ion
{
	namespace Scene
	{

		bool IsUniformNameArrayElement(string const & Label, int & Index, string & LHS, string & Remaining);

		class CRenderPass
		{

		public:

			CRenderPass(Graphics::IGraphicsAPI * GraphicsAPI, SharedPointer<Graphics::IGraphicsContext> GraphicsContext);
			virtual void SetRenderTarget(SharedPointer<Graphics::IRenderTarget> RenderTarget);

			virtual string const & GetName() const;
			virtual Graphics::IGraphicsAPI * GetGraphicsAPI();
			virtual SharedPointer<Graphics::IGraphicsContext> GetGraphicsContext();

			virtual ICamera * GetActiveCamera();
			virtual ICamera const * GetActiveCamera() const;
			virtual void SetActiveCamera(ICamera * Camera);

			virtual void AddLight(ILight * Light);
			//virtual void RemoveLight(ILight * Light);

			virtual void AddSceneObject(ISceneObject * SceneObject);
			virtual void RemoveSceneObject(ISceneObject * SceneObject);

			virtual void Load();
			virtual void Draw();

			virtual void PreparePipelineStateForRendering(SharedPointer<Graphics::IPipelineState> PipelineState, ISceneObject * SceneObject);
			virtual void SubmitPipelineStateForRendering(SharedPointer<Graphics::IPipelineState> PipelineState, ISceneObject * SceneObject, uint const InstanceCount = 1, uint const RenderCategory = 0);

		protected:

			ICamera * ActiveCamera = nullptr;
			set<ISceneObject *> SceneObjects;
			set<ILight *> Lights;
			map<string, SharedPointer<Graphics::IUniform>> Uniforms;
			vector<vector<std::tuple<ISceneObject *, SharedPointer<Graphics::IPipelineState>, uint>>> RenderQueue;
			string Name;

			Graphics::IGraphicsAPI * GraphicsAPI = nullptr;
			std::shared_ptr<Graphics::IGraphicsContext> GraphicsContext;
			std::shared_ptr<Graphics::IRenderTarget> RenderTarget;

			SharedPointer<Graphics::CUniformValue<glm::mat4>> uProjectionMatrix = std::make_shared<Graphics::CUniformValue<glm::mat4>>();
			SharedPointer<Graphics::CUniformValue<glm::mat4>> uViewMatrix = std::make_shared<Graphics::CUniformValue<glm::mat4>>();
			SharedPointer<Graphics::CUniformValue<vec3f>> uCameraPosition = std::make_shared<Graphics::CUniformValue<vec3f>>();
			SharedPointer<Graphics::CUniformValue<glm::mat4>> uModelMatrix = std::make_shared<Graphics::CUniformValue<glm::mat4>>();
			SharedPointer<Graphics::CUniformValue<glm::mat4>> uNormalMatrix = std::make_shared<Graphics::CUniformValue<glm::mat4>>();

			struct SLightUniformMatrixRow
			{
				vector<map<string, SharedPointer<Graphics::IUniform>>> Entries;
				SharedPointer<Graphics::CUniformValue<int>> CountUniform = std::make_shared<Graphics::CUniformValue<int>>(0);
			};
			map<string, SLightUniformMatrixRow> LightUniformMatrix;

			void RebuildLightUniformMatrix();


		};

	}
}
