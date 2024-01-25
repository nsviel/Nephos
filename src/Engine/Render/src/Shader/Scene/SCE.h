#pragma once

#include <Engine/Render/src/Shader/Base/BASE_shader.h>
#include <Utility/Specific/common.h>

class Engine;
namespace utl::element{class Window;}


namespace eng::shader{

class SCE : public BASE_shader
{
public:
  SCE(Engine* engine);
  ~SCE();

  //Main function
  void init_shader();

private:
  utl::element::Window* utl_window;
};

}
