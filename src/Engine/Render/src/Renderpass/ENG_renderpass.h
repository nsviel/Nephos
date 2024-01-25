#pragma once

#include <Utility/Specific/common.h>

class Engine;
namespace eng::renderpass{class EDL;}
namespace eng::renderpass{class Scene;}
namespace eng::renderpass{class Glyph;}
namespace eng::renderpass{class GUI;}


namespace eng::renderpass{

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
  eng::renderpass::Scene* rp_scene;
  eng::renderpass::Glyph* rp_glyph;
  eng::renderpass::EDL* rp_edl;
  eng::renderpass::GUI* rp_gui;
};

}
