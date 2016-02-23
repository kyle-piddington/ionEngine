
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

			CRenderPass();

			virtual string const & GetName() const;
			virtual Graphics::IGraphicsAPI * GetGraphicsAPI();
			virtual void SetGraphicsAPI(Graphics::IGraphicsAPI * GraphicsAPI);

			virtual ICamera * GetActiveCamera();
			virtual ICamera const * GetActiveCamera() const;
			virtual void SetActiveCamera(ICamera * Camera);

			virtual void AddLight(ILight * Light);
			//virtual void RemoveLight(ILight * Light);

			virtual void AddSceneObject(ISceneObject * SceneObject);
			virtual void RemoveSceneObject(ISceneObject * SceneObject);

			virtual void Load();
			virtual void Draw();

			virtual void PreparePipelineStateForRendering(Graphics::IPipelineState * PipelineState, ISceneObject * SceneObject);
			virtual void SubmitPipelineStateForRendering(Graphics::IPipelineState * PipelineState, ISceneObject * SceneObject, uint const RenderCategory = 0);

		protected:

			ICamera * ActiveCamera = nullptr;
			set<ISceneObject *> SceneObjects;
			set<ILight *> Lights;
			map<string, Graphics::IUniform *> Uniforms;
			vector<vector<pair<ISceneObject *, Graphics::IPipelineState *>>> RenderQueue;
			string Name;

			Graphics::CUniformValue<glm::mat4> uProjectionMatrix;
			Graphics::CUniformValue<glm::mat4> uViewMatrix;
			Graphics::CUniformValue<vec3f> uCameraPosition;
			Graphics::CUniformValue<glm::mat4> uModelMatrix;
			Graphics::CUniformValue<glm::mat4> uNormalMatrix;

			struct SLightUniformMatrixRow
			{
				vector<map<string, Graphics::IUniform *>> Entries;
				Graphics::CUniformValue<uint> CountUniform;
			};
			map<string, SLightUniformMatrixRow> LightUniformMatrix;

			void RebuildLightUniformMatrix();

			Graphics::IGraphicsAPI * GraphicsAPI = nullptr;

		};

	}
}
