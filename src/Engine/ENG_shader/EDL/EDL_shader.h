#ifndef SHADER_EDL_H
#define SHADER_EDL_H

#include <ENG_shader/EDL/EDL_param.h>
#include <ENG_shader/Base/BASE_shader.h>
#include <UTL_specific/common.h>

class Engine;
class Struct_camera;
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
  Struct_camera* camera;
  UTL_window* utl_window;
  EDL_param* edl_param;
};

#endif
