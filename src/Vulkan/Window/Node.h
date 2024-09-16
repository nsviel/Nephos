#pragma once

#include <Utility/Base/Class/Node.h>

namespace vk{class Structure;}
namespace vk::window{class Window;}
namespace vk::window{class Event;}


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
  vk::window::Window* vk_window;
  vk::window::Event* vk_event;
};

}
