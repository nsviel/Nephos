#pragma once

#include "PSR_param.h"
#include <Engine/ENG_shader/Base/BASE_shader.h>
#include <Engine/ENG_camera/Struct_camera.h>
#include <Utility/UTL_specific/common.h>

class Engine;
class Struct_camera;
class UTL_window;


class PSR_shader : public BASE_shader
{
public:
  PSR_shader(Engine* engine);
  ~PSR_shader();

  //Main function
  void update_shader();
  void init_shader();

  inline PSR_param* get_pyramid_param(){return psr_param;}

private:
  UTL_window* utl_window;
  PSR_param* psr_param;

  Struct_camera* camera;
};
