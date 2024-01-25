#pragma once

#include <Utility/Specific/common.h>

class Engine;
namespace eng::renderpass{class RP_edl;}
namespace eng::renderpass{class RP_scene;}
namespace eng::renderpass{class RP_glyph;}
namespace eng::renderpass{class RP_gui;}


class ENG_renderpass
{
public:
  //Constructor / Destructor
  ENG_renderpass(Engine* engine);
  ~ENG_renderpass();

public:
  //Main functions
  void init();

private:
  eng::renderpass::RP_scene* rp_scene;
  eng::renderpass::RP_glyph* rp_glyph;
  eng::renderpass::RP_edl* rp_edl;
  eng::renderpass::RP_gui* rp_gui;
};
