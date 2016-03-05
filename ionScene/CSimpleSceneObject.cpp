
#include "CSimpleSceneObject.h"
#include "CRenderPass.h"


namespace ion
{
	namespace Scene
	{

		SSimpleMaterial::SSimpleMaterial()
		{
			LoadDefaults();
		}

		void SSimpleMaterial::LoadDefaults()
		{
			*Shininess = 1000.0f;
			*Ambient = SColorf(0.05f);
			*Diffuse = SColorf(0.9f);
			*Specular = SColorf(1.f);
		}

		CSimpleSceneObject::~CSimpleSceneObject()
		{}

		void CSimpleSceneObject::Load(CRenderPass * RenderPass)
		{
			if (! IndexBuffer || ! VertexBuffer || ! Shader)
			{
				return;
			}

			if (! PipelineState)
			{
				PipelineState = RenderPass->GetGraphicsContext()->CreatePipelineState();
			}

			PipelineState->SetIndexBuffer(IndexBuffer);
			PipelineState->SetVertexBuffer(0, VertexBuffer);

			PipelineState->SetProgram(Shader);

			std::for_each(Textures.begin(), Textures.end(), [this](pair<string, SharedPtr<Graphics::ITexture>> const & Iterator)
			{
				PipelineState->SetTexture(Iterator.first, Iterator.second);
			});
			std::for_each(Uniforms.begin(), Uniforms.end(), [this](pair<string, SharedPtr<Graphics::IUniform>> const & Iterator)
			{
				PipelineState->SetUniform(Iterator.first, Iterator.second);
			});

			PipelineState->OfferUniform("uMaterial.AmbientColor", Material.Ambient);
			PipelineState->OfferUniform("uMaterial.DiffuseColor", Material.Diffuse);
			PipelineState->OfferUniform("uMaterial.SpecularColor", Material.Specular);
			PipelineState->OfferUniform("uMaterial.Shininess", Material.Shininess);

			RenderPass->PreparePipelineStateForRendering(PipelineState, this);
			Loaded = true;
		}

		void CSimpleSceneObject::Draw(CRenderPass * RenderPass)
		{
			if (PipelineState)
			{
				RenderPass->SubmitPipelineStateForRendering(PipelineState, this);
			}
		}

		void CSimpleSceneObject::SetIndexBuffer(SharedPtr<Graphics::IIndexBuffer> IndexBuffer)
		{
			this->IndexBuffer = IndexBuffer;
		}

		void CSimpleSceneObject::SetVertexBuffer(SharedPtr<Graphics::IVertexBuffer> VertexBuffer)
		{
			this->VertexBuffer = VertexBuffer;
		}

		void CSimpleSceneObject::SetShader(SharedPtr<Graphics::IShaderProgram> Shader)
		{
			this->Shader = Shader;
			Loaded = false;
		}

		void CSimpleSceneObject::SetTexture(string const & Name, SharedPtr<Graphics::ITexture> Texture)
		{
			if (Texture)
			{
				Textures[Name] = Texture;
			}
			else
			{
				Textures.erase(Name);
			}
			Loaded = false;
		}

		void CSimpleSceneObject::SetUniform(string const & Name, SharedPtr<Graphics::IUniform> Uniform)
		{
			if (Uniform)
			{
				Uniforms[Name] = Uniform;
			}
			else
			{
				Uniforms.erase(Name);
			}
			Loaded = false;
		}

		void CSimpleSceneObject::SetFeatureEnabled(Graphics::EDrawFeature const Feature, bool const Enabled)
		{
			if (PipelineState)
			{
				PipelineState->SetFeatureEnabled(Feature, Enabled);
			}
		}

		SSimpleMaterial & CSimpleSceneObject::GetMaterial()
		{
			return Material;
		}

		SSimpleMaterial const & CSimpleSceneObject::GetMaterial() const
		{
			return Material;
		}

		void CSimpleSceneObject::SetMaterial(SSimpleMaterial const & Material)
		{
			this->Material = Material;
		}

	}
}