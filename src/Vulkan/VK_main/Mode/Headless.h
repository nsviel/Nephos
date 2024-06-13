#pragma once

#include <Vulkan/VK_main/Engine.h>
#include <Utility/Specific/Common.h>

namespace vk::structure{class Vulkan;}
namespace vk::draw{class Headless;}


namespace vk::main{

class Headless : public vk::main::Engine
{
public:
  //Constructor / Destructor
  Headless(vk::structure::Vulkan* vk_struct);
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
