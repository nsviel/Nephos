#ifndef SHADER_PSR_H
#define SHADER_PSR_H

#include "PSR_param.h"
#include <ENG_shader/Base/BASE_shader.h>
#include <ELE_specific/common.h>

class Engine;
class Param;
class ELE_window;


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
  Param* param;
  ELE_window* ele_window;
  PSR_param* psr_param;
};

#endif
