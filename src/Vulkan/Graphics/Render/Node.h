#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Structure;}
namespace vk::postprocess{class Renderpass;}
namespace vk::geometry{class Renderpass;}
namespace vk::gfx::presentation{class Renderpass;}


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

private:
  vk::Structure* vk_struct;
  vk::geometry::Renderpass* rp_scene;
  vk::postprocess::Renderpass* rp_edl;
  vk::gfx::presentation::Renderpass* rp_gui;
};

}
