#pragma once

namespace vk{class Structure;}
namespace vk::draw{class Renderer;}
namespace vk::synchro{class Fence;}
namespace vk::synchro{class Semaphore;}
namespace vk::structure{class Object;}


namespace vk::draw{

class Headless
{
public:
  //Constructor / Destructor
  Headless(vk::Structure* vk_struct);
  ~Headless();

public:
  //Main function
  void draw_frame();

private:
  vk::Structure* vk_struct;
  vk::draw::Renderer* vk_render;
  vk::synchro::Fence* vk_fence;
  vk::synchro::Semaphore* vk_semaphore;
};

}
