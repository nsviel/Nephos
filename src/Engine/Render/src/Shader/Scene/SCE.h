#pragma once

#include <Utility/Base/Shader/BASE_shader.h>
#include <Utility/Specific/common.h>

class Engine;
namespace utl::element{class Window;}


namespace eng::shader{

class SCE : public utl::base::BASE_shader
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
