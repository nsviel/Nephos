#pragma once

namespace vk::commandbuffer{class Command_buffer;}
namespace vk::commandbuffer{class Allocator;}
namespace vk{class Structure;}
namespace vk::structure{class Fence;}
namespace vk::structure{class Render;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Command_buffer;}
namespace vk::synchro{class Semaphore;}
namespace sys::timer{class Chrono;}


namespace vk::draw{

class Renderpass
{
public:
  //Constructor / Destructor
  Renderpass(vk::Structure* vk_struct);
  ~Renderpass();

public:
  //Main function
  void run_renderpass(vk::structure::Render& render);

  //Subfunction
  void prepare_renderpass(vk::structure::Render& render);
  void start_renderpass(vk::structure::Render& render);
  void draw_subpass(vk::structure::Render& render);
  void stop_renderpass(vk::structure::Render& render);
  void cmd_next_subset(vk::structure::Render& render);
  void prepare_command(vk::structure::Render& render);

private:
  vk::Structure* vk_struct;
  vk::commandbuffer::Command_buffer* vk_command;
  vk::commandbuffer::Allocator* vk_allocator;
  vk::synchro::Semaphore* vk_semaphore;
  sys::timer::Chrono* utl_chrono;
};

}
