#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Shader/Base/BASE_shader.h>

class Engine;
class UTL_window;


namespace eng::shader{

class SCE_shader : public BASE_shader
{
public:
  SCE_shader(Engine* engine);
  ~SCE_shader();

  //Main function
  void init_shader();

private:
  UTL_window* utl_window;
};

}
