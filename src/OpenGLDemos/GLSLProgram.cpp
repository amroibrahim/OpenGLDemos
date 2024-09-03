#include "GLSLProgram.h"

GLSLProgram::GLSLProgram() : _handle(glCreateProgram())
{
}

void GLSLProgram::CompileShader(const std::string& program, GLSLShaderType type)
{
  // Create shader handle
  GLuint shader_handle = glCreateShader(type);

  // Compile shader
  const char* shader_source = program.c_str();
  glShaderSource(shader_handle, 1, &shader_source, nullptr);
  glCompileShader(shader_handle);

  _shaders_Lookup[type] = shader_handle;
}

bool GLSLProgram::AttachShader(GLSLShaderType type, std::string& error)
{
  // Get shader handle
  GLuint shader_handle = _shaders_Lookup[type];

  // Check compilation status
  GLint compile_status;
  glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &compile_status);

  // Check for errors
  if (compile_status != GL_TRUE)
  {
    GLint log_length;
    glGetShaderiv(shader_handle, GL_INFO_LOG_LENGTH, &log_length);
    std::string log(log_length, ' ');
    glGetShaderInfoLog(shader_handle, log_length, &log_length, &log[0]);
    error = log;
    return false;
  }
  else
  {
    glAttachShader(_handle, shader_handle);
    return true;
  }
}

bool GLSLProgram::Link(std::string& error)
{
  // Link program
  glLinkProgram(_handle);

  // Check link status
  GLint link_status;
  glGetProgramiv(_handle, GL_LINK_STATUS, &link_status);

  // Check for errors
  if (link_status != GL_TRUE)
  {
    GLint log_length;
    glGetProgramiv(_handle, GL_INFO_LOG_LENGTH, &log_length);
    std::string log(log_length, ' ');
    glGetProgramInfoLog(_handle, log_length, &log_length, &log[0]);
    error = log;
    return false;
  }

  return true;
}

void GLSLProgram::Use() const
{
  glUseProgram(_handle);
}

void GLSLProgram::Unuse() const
{
  glUseProgram(0);
}
