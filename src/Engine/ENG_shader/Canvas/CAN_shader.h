#ifndef SHADER_CANVAS_H
#define SHADER_CANVAS_H

#include <ELE_specific/common.h>
#include <ENG_shader/Base/BASE_shader.h>

class Engine;
class ELE_window;


class CAN_shader : public BASE_shader
{
public:
  CAN_shader(Engine* engine);
  ~CAN_shader();

  //Main function
  void init_shader();

private:
  ELE_window* ele_window;
};

#endif
