#ifndef SHADER_SCENE_H
#define SHADER_SCENE_H

#include <ELE_specific/common.h>
#include <ENG_shader/Base/BASE_shader.h>

class Engine;
class Window;


class SCE_shader : public BASE_shader
{
public:
  SCE_shader(Engine* engine);
  ~SCE_shader();

  //Main function
  void init_shader();

private:
  Window* window;
};

#endif
