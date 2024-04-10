#pragma once

#include <Utility/Specific/Common.h>

namespace eng::render{class Node;}
namespace rnd::edl{class Renderpass;}
namespace eng::renderpass{class Scene;}
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
  rnd::edl::Renderpass* rp_edl;
  eng::renderpass::GUI* rp_gui;
};

}
