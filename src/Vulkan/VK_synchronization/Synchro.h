#pragma once

namespace vk::structure{class Vulkan;}


namespace vk::synchro{

class Synchro
{
public:
  //Constructor / Destructor
  Synchro(vk::structure::Vulkan* vk_struct);
  ~Synchro();

public:
  //Main function
  void wait_idle();
  void wait_idle_and_pause();
  void end_idle();

private:
  vk::structure::Vulkan* vk_struct;
};

}
