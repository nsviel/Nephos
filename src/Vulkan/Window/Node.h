#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Structure;}
namespace vk::window{class GLFW;}


namespace vk::window{

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
  void clean();

private:
  vk::Structure* vk_struct;
  vk::window::GLFW* vk_window;
};

}
