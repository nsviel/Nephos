#pragma once

#include <Vulkan/Render/VK_engine/Engine/Engine.h>

namespace vk{class Structure;}
namespace vk::draw{class Graphical;}
namespace vk::window{class Window;}


namespace vk::main{

class Graphical : public vk::main::Engine
{
public:
  //Constructor / Destructor
  Graphical(vk::Structure* vk_struct);
  ~Graphical();

public:
  //Main function
  void init();
  void loop();
  void clean();

private:
  vk::draw::Graphical* vk_drawer;
  vk::window::Window* vk_window;
};

}
