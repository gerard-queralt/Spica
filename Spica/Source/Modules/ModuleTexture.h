#pragma once

#include "Module.h"

#include <string>
#include <glew.h>
#include "DirectXTex/DirectXTex.h"

class ModuleTexture : public Module
{
public:
	ModuleTexture();
	~ModuleTexture();

	static const std::string s_textureFolderPath;

	GLuint LoadTextureFromFile(std::string i_texturePathInModel, std::string i_modelPath) const;

private:
	HRESULT LoadImageFromFile(const std::string& i_texturePathInModel,
							  const std::string& i_modelPath,
							  DirectX::ScratchImage& o_image) const;
	std::string GetImageNameFromPath(const std::string& i_texturePathInModel) const;
	HRESULT TryLoadingImage(std::string i_texturePath, DirectX::ScratchImage& o_image) const;
	HRESULT RotateImage(const DirectX::ScratchImage& i_imageSource, DirectX::ScratchImage& o_rotatedImage) const;
	void LoadInformationFromImage(const DirectX::ScratchImage& i_image,
		GLint& o_width,
		GLint& o_height,
		GLint& o_internalFormat,
		GLint& o_format,
		GLint& o_type) const;
};

