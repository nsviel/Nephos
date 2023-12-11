#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Shader/Base/BASE_shader.h>

class Engine;
class UTL_window;


namespace eng::shader{

class SCE : public BASE_shader
{
public:
  SCE(Engine* engine);
  ~SCE();

  //Main function
  void init_shader();

private:
  UTL_window* utl_window;
};

}
