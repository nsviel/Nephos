#pragma once

#include "PSR_param.h"
#include <Engine/Shader/Base/BASE_shader.h>
#include <Engine/Base/Namespace.h>
#include <Utility/Specific/common.h>

class Engine;

class UTL_window;


namespace eng::shader{

class PSR : public BASE_shader
{
public:
  PSR(Engine* engine);
  ~PSR();

  //Main function
  void update_shader();
  void init_shader();

  inline PSR_param* get_pyramid_param(){return psr_param;}

private:
  UTL_window* utl_window;
  PSR_param* psr_param;

  eng::structure::Camera* camera;
};

}
