#include "TriangleScene.h"

void TriangleScene::Initialize(Subsystems* configuration)
{
  Scene::Initialize(configuration);

  const char* vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\0";

  const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0f);\n"
    "}\n\0";

  std::string _error;

  _shader_program.CompileShader(vertexShaderSource, GL_VERTEX_SHADER);
  if (!_shader_program.AttachShader(GL_VERTEX_SHADER, _error))
  {
    _configuration->logger.Log("Vertex Shader Error: %s\n", _error.c_str());
  }
  
  _shader_program.CompileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

  if (!_shader_program.AttachShader(GL_FRAGMENT_SHADER, _error))
  {
    _configuration->logger.Log("Fragment Shader Error: %s\n", _error.c_str());
  }

  if (!_shader_program.Link(_error)) 
  {
    _configuration->logger.Log("Shader Link Error: %s\n", _error.c_str());
  }

  

  float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

  };

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
}

void TriangleScene::HandleInput(const Uint8* keybaord_states, int mouse_x, int mouse_y, Uint32 mouse_states)
{

}

void TriangleScene::Update(float delta_time)
{

}

void TriangleScene::Render()
{  
  _shader_program.Use();

  glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void TriangleScene::Clean()
{
  _shader_program.Unuse();
}
