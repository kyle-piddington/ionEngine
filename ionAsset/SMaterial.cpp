
#include "SMaterial.h"


SMaterial::SMaterial()
{
	LoadDefaults();
}

void SMaterial::LoadDefaults()
{
	Shininess = 1000.0f;
	Ambient = SColorf(0.15f, 0.15f, 0.15f);
	Diffuse = SColorf(0.8f, 0.8f, 0.8f);
	Specular = SColorf(1.f, 1.f, 1.f);
}

void SMaterial::SetTexture(uint const Layer, CTexture * const Texture)
{
	if (Layer >= Textures.size())
		Textures.resize(Layer + 1, 0);
	Textures[Layer] = Texture;

	std::vector<CTexture *>::iterator it = Textures.end();

	while (it != Textures.begin())
	{
		it --;
		if (* it)
			break;
		it = Textures.erase(it);
	}
}
