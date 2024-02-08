#pragma once

#include <Utility/Specific/common.h>

namespace vk::render{class Node;}
namespace vk::renderpass{class EDL;}
namespace vk::renderpass{class Scene;}
namespace vk::renderpass{class GUI;}


namespace vk::renderpass{

class Manager
{
public:
  //Constructor / Destructor
  Manager(vk::render::Node* node_render);
  ~Manager();

public:
  //Main functions
  void init();

private:
  vk::renderpass::Scene* rp_scene;
  vk::renderpass::EDL* rp_edl;
  vk::renderpass::GUI* rp_gui;
};

}
