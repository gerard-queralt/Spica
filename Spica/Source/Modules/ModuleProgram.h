#pragma once

#include "Module.h"
#include <string>
#include <glew.h>

class ModuleProgram : public Module
{
public:
	ModuleProgram();
	~ModuleProgram();

	static const std::string s_shaderFolderPath;

	GLuint CreateProgramFromShaders(const std::string& i_vertexShaderName, const std::string& i_fragmentShaderName) const;

private:
	std::string ReadShaderFile(const std::string& i_fileName) const;
	GLuint CompileShader(GLenum i_shaderType, const std::string& i_shaderSource) const;
	GLuint CreateProgram(GLuint i_vertexShader, GLuint i_fragmentShader) const;
};

