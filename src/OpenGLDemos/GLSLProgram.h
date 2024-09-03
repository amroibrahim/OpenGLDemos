#pragma once

#include <string>
#include <map>

#include <glad/glad.h>


typedef uint32_t GLSLShaderType;
class GLSLProgram
{
public:
  GLSLProgram();
  ~GLSLProgram() = default;

  GLSLProgram(const GLSLProgram&) = delete;
  GLSLProgram& operator=(const GLSLProgram&) = delete;

  void CompileShader(const std::string& program, GLSLShaderType type);

  bool AttachShader(GLSLShaderType type, std::string& error);
  bool Link(std::string& error);

  void Use() const;
  void Unuse() const;

protected:
  std::map<GLSLShaderType, GLuint> _shaders_Lookup;

  GLuint _handle;
};

