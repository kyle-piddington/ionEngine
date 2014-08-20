
#include "CSceneNode.h"

#include "CScene.h"


CSceneNode::CSceneNode(CScene * Scene, ISceneNode * Parent)
: ISceneNode(Parent)
{
	this->Scene = Scene;
	TransformationUniform.Value = & AbsoluteTransformation;
}

void CSceneNode::Update()
{
	for (auto it : Components)
		it.second->Update(this);

	ISceneNode::Update();
}

static void RecurseMesh(CSceneNode * SceneNode, CShader * Shader, vector<CDrawConfig *> & Definitions, SMeshNode * Node);

map<CShader *, vector<CDrawConfig *>> CSceneNode::PrepareDrawConfigurations(IRenderPass * Pass)
{
	auto Configurations = ISceneNode::PrepareDrawConfigurations(Pass);

	if (Mesh && (! CheckMapAccess(DrawConfigurations[Pass], Shaders[Pass]) || Dirty))
	{
		vector<CDrawConfig *> DrawDefinitions;

		RecurseMesh(this, Shaders[Pass], DrawDefinitions, Mesh->Root);

		auto ActiveUniforms = Shaders[Pass]->GetActiveUniforms();

		for (auto & ActiveUniform : ActiveUniforms)
		{
			auto Uniform = Scene->GetUniform(ActiveUniform.first);
			if (Uniform)
				for (auto & Definition : DrawDefinitions)
					Definition->AddUniform(ActiveUniform.first, Uniform);
		}

		for (auto & Uniform : Uniforms)
			for (auto & Definition : DrawDefinitions)
				Definition->AddUniform(Uniform.first, Uniform.second);

		for (auto & Definition : DrawDefinitions)
		{
			for (uint i = 0; i < Textures.size(); ++ i)
			{
				if (Textures[i])
				{
					stringstream Label;
					Label << "Texture";
					Label << i;
					Definition->AddTexture(Label.str(), Textures[i]);
				}
			}
		}

		DrawConfigurations[Pass][Shaders[Pass]] = DrawDefinitions;

		Dirty = false;
	}

	for (auto Shader : DrawConfigurations[Pass])
		AddAtEnd(Configurations[Shader.first], Shader.second);

	return Configurations;
}

static void RecurseMesh(CSceneNode * SceneNode, CShader * Shader, vector<CDrawConfig *> & Definitions, SMeshNode * Node)
{
	for (auto & Buffer : Node->Buffers)
	{
		CDrawConfig * DrawConfig = new CDrawConfig{Shader};

		DrawConfig->OfferVertexBuffer("Position", Buffer->VertexBuffers.Positions);
		DrawConfig->OfferVertexBuffer("Color", Buffer->VertexBuffers.Colors);
		DrawConfig->OfferVertexBuffer("Normal", Buffer->VertexBuffers.Normals);
		DrawConfig->OfferVertexBuffer("TexCoord", Buffer->VertexBuffers.TexCoords);
		DrawConfig->SetIndexBuffer(Buffer->VertexBuffers.Indices);

		DrawConfig->OfferUniform("Model", & SceneNode->GetTransformationUniform());
		DrawConfig->OfferUniform("Local", & Node->AbsoluteTransformation);

		Definitions.push_back(DrawConfig);
	}
	
	for (auto & Child : Node->GetChildren())
	{
		RecurseMesh(SceneNode, Shader, Definitions, Child);
	}
}

void CSceneNode::ResetDrawConfigurations()
{
	for (auto Pass : DrawConfigurations)
	{
		for (auto Shader : Pass.second)
			for (auto Config : Shader.second)
				delete Config;
		Pass.second.clear();
	}
}

CScene * CSceneNode::GetScene()
{
	return Scene;
}

CUniformReference<glm::mat4> & CSceneNode::GetTransformationUniform()
{
	return TransformationUniform;
}


//////////
// Mesh //
//////////

void CSceneNode::SetMesh(CMesh * Mesh)
{
	this->Mesh = Mesh;
	Dirty = true;
}

CMesh * CSceneNode::GetMesh()
{
	return Mesh;
}


/////////////
// Shaders //
/////////////

void CSceneNode::SetShader(CShader * Shader, IRenderPass * RenderPass)
{
	this->Shaders[RenderPass] = Shader;
	Dirty = true;
}

void CSceneNode::SetUniform(string const & Label, IUniform * Uniform)
{
	Uniforms[Label] = Uniform;
	Dirty = true;
}

CShader * CSceneNode::GetShader(IRenderPass * RenderPass)
{
	return Shaders[RenderPass];
}

IUniform * CSceneNode::GetUniform(string const & Label)
{
	return Uniforms[Label];
}

map<string, IUniform *> & CSceneNode::GetUniforms()
{
	return Uniforms;
}


//////////////
// Textures //
//////////////

uint CSceneNode::GetTextureCount() const
{
	return Textures.size();
}

CTexture * CSceneNode::GetTexture(uint const Index)
{
	if (Textures.size() >= Index)
		return Textures[Index];
	return 0;
}

ion::GL::UniformValue<int> * CSceneNode::GetTextureUniform(uint const Index)
{
	if (TextureUniforms.size() >= Index)
		return TextureUniforms[Index];
	return 0;
}

vector<CTexture *> & CSceneNode::GetTextures()
{
	return Textures;
}

vector<ion::GL::UniformValue<int> *> & CSceneNode::GetTextureUniforms()
{
	return TextureUniforms;
}

void CSceneNode::SetTexture(uint const Index, CTexture * Texture)
{
	if (Index >= Textures.size())
	{
		Textures.resize(Index + 1, nullptr);
		TextureUniforms.resize(Index + 1, nullptr);
	}

	Textures[Index] = Texture;
	if (! TextureUniforms[Index])
		TextureUniforms[Index] = new ion::GL::UniformValue<int>(Index);

	Dirty = true;
}
