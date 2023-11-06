#ifndef ELE_RENDERPASS_H
#define ELE_RENDERPASS_H

#include <ELE_specific/common.h>

class Engine;
class ENG_scene;
class ENG_edl;
class ENG_gui;


class ENG_renderpass
{
public:
  //Constructor / Destructor
  ENG_renderpass(Engine* engine);
  ~ENG_renderpass();

public:
  //Main functions
  void init_renderpass();

private:
  ENG_scene* eng_scene;
  ENG_edl* eng_edl;
  ENG_gui* eng_gui;
};

#endif
