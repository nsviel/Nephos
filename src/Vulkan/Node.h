#pragma once

#include <Utility/Base/Class/Node.h>

namespace utl{class Node;}
namespace vk{class Structure;}
namespace vk{class Interface;}
namespace vk::core{class Node;}
namespace vk::render{class Node;}
namespace vk::window{class Node;}


namespace vk{

class Node : public utl::base::Node
{
public:
  //Constructor / Destructor
  Node(bool* running);
  ~Node();

public:
  //Main function
  void init();
  void loop();
  void clean();

  inline vk::Structure* get_vk_struct(){return vk_struct;}
  inline vk::Interface* get_vk_interface(){return vk_interface;}

private:
  vk::Structure* vk_struct;
  vk::Interface* vk_interface;
  vk::render::Node* vk_render;
  vk::core::Node* vk_core;
  vk::window::Node* vk_window;
};

}
