#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Element/Namespace.h>
#include <Engine/Shader/Base/BASE_shader.h>

class Engine;


namespace eng::shader{

class SCE : public BASE_shader
{
public:
  SCE(Engine* engine);
  ~SCE();

  //Main function
  void init_shader();

private:
  util::element::Window* utl_window;
};

}
