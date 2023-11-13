#ifndef SHADER_SCENE_H
#define SHADER_SCENE_H

#include <UTL_specific/common.h>
#include <ENG_shader/Base/BASE_shader.h>

class Engine;
class UTL_window;


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

#endif
