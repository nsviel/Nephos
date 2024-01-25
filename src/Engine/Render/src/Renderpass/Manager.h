#pragma once

#include <Utility/Specific/common.h>

namespace eng::render{class Node;}
namespace eng::renderpass{class EDL;}
namespace eng::renderpass{class Scene;}
namespace eng::renderpass{class Glyph;}
namespace eng::renderpass{class GUI;}


namespace eng::renderpass{

class Manager
{
public:
  //Constructor / Destructor
  Manager(eng::render::Node* node_render);
  ~Manager();

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
