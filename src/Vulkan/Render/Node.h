#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Structure;}
namespace vk::draw{class Graphical;}
namespace vk::main{class Profiler;}
namespace vk::render::edl{class Renderpass;}
namespace vk::render::geometry{class Renderpass;}
namespace vk::render::onscreen{class Renderpass;}


namespace vk::render{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(vk::Structure* vk_struct);
  ~Node();

public:
  //Main function
  void init();
  void loop();

private:
  vk::Structure* vk_struct;
  vk::main::Profiler* vk_profiler;
  vk::draw::Graphical* vk_drawer;
  vk::render::geometry::Renderpass* rp_scene;
  vk::render::edl::Renderpass* rp_edl;
  vk::render::onscreen::Renderpass* rp_gui;
};

}
