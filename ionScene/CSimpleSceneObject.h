
#pragma once

#include "ISceneObject.h"
#include "CSimpleMesh.h"


namespace ion
{
	namespace Scene
	{

		struct SSimpleMaterial
		{

			SSimpleMaterial();
			void LoadDefaults();

			SharedPtr<Graphics::CUniformValue<color3f>> Ambient = std::make_shared<Graphics::CUniformValue<color3f>>();
			SharedPtr<Graphics::CUniformValue<color3f>> Diffuse = std::make_shared<Graphics::CUniformValue<color3f>>();
			SharedPtr<Graphics::CUniformValue<color3f>> Specular = std::make_shared<Graphics::CUniformValue<color3f>>();
			SharedPtr<Graphics::CUniformValue<f32>> Shininess = std::make_shared<Graphics::CUniformValue<f32>>();

		};

		class CSimpleSceneObject : public ISceneObject
		{

		public:

			~CSimpleSceneObject();

			virtual void Load(CRenderPass * RenderPass);
			virtual void Draw(CRenderPass * RenderPass);

			virtual void SetIndexBuffer(SharedPtr<Graphics::IIndexBuffer> IndexBuffer);
			virtual void SetVertexBuffer(SharedPtr<Graphics::IVertexBuffer> VertexBuffer);
			virtual void SetShader(SharedPtr<Graphics::IShaderProgram> Shader);
			virtual void SetTexture(string const & Name, SharedPtr<Graphics::ITexture> Texture);
			virtual void SetUniform(string const & Name, SharedPtr<Graphics::IUniform> Uniform);
			virtual void SetFeatureEnabled(Graphics::EDrawFeature const Feature, bool const Enabled);

			virtual SSimpleMaterial & GetMaterial();
			virtual SSimpleMaterial const & GetMaterial() const;
			virtual void SetMaterial(SSimpleMaterial const & Material);

		protected:

			SharedPtr<Graphics::IPipelineState> PipelineState;
			SharedPtr<Graphics::IShaderProgram> Shader;
			SharedPtr<Graphics::IIndexBuffer> IndexBuffer;
			SharedPtr<Graphics::IVertexBuffer> VertexBuffer;
			SSimpleMaterial Material;

			map<string, SharedPtr<Graphics::ITexture>> Textures;
			map<string, SharedPtr<Graphics::IUniform>> Uniforms;

		};

	}
}