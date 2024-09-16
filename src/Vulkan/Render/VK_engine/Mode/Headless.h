#pragma once

#include <Vulkan/Render/VK_engine/Engine/Engine.h>

namespace vk{class Structure;}
namespace vk::draw{class Headless;}


namespace vk::main{

class Headless : public vk::main::Engine
{
public:
  //Constructor / Destructor
  Headless(vk::Structure* vk_struct);
  ~Headless();

public:
  //Main function
  void init();
  void loop();
  void clean();

private:
  vk::draw::Headless* vk_drawer;
};

}
