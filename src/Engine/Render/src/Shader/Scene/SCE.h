#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Element/src/Namespace.h>
#include <Engine/Render/src/Shader/Base/BASE_shader.h>

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
  utl::element::Window* utl_window;
};

}
