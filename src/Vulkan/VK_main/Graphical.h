#pragma once

#include <Vulkan/VK_main/Engine.h>
#include <Utility/Specific/Common.h>

namespace vk::structure{class Vulkan;}


namespace vk::main{

class Graphical : public vk::main::Engine
{
public:
  //Constructor / Destructor
  Graphical(vk::structure::Vulkan* vk_struct);
  ~Graphical();

public:
  //Main functions
  void init();
  void loop();
  void clean();

private:
};

}
