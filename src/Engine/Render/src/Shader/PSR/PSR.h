#pragma once

#include "PSR_param.h"
#include <Engine/Render/src/Shader/Base/BASE_shader.h>

#include <Engine/Camera/Namespace.h>
#include <Utility/Specific/common.h>
#include <Utility/Element/src/Namespace.h>

class Engine;


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
  utl::element::Window* utl_window;
  PSR_param* psr_param;

  eng::cam::Manager* cam_manager;
};

}
