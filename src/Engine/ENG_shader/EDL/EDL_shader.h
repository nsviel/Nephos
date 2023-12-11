#pragma once

#include <Engine/Base/Namespace.h>
#include <Engine/ENG_shader/EDL/EDL_param.h>
#include <Engine/ENG_shader/Base/BASE_shader.h>
#include <Utility/UTL_specific/common.h>

class Engine;

class UTL_window;


class EDL_shader : public BASE_shader
{
public:
  //Contrustor / destructor
  EDL_shader(Engine* engine);
  ~EDL_shader();

  //Main function
  void init_shader();
  void update_shader();

  inline EDL_param* get_edl_param(){return edl_param;}

private:
  eng::structure::Struct_camera* camera;
  UTL_window* utl_window;
  EDL_param* edl_param;
};
