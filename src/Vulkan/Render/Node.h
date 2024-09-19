#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Structure;}
namespace vk::draw{class Graphical;}
namespace vk::render{class Render;}


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
  vk::draw::Graphical* vk_drawer;
  vk::render::Render* vk_render;
};

}
