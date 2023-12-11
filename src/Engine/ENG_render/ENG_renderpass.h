#pragma once

#include <Utility/Specific/common.h>

class Engine;
class RP_scene;
class RP_edl;
class RP_gui;


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
  RP_scene* rp_scene;
  RP_edl* rp_edl;
  RP_gui* rp_gui;
};
