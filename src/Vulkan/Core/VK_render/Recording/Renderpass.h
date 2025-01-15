#pragma once

#include <memory>

namespace vk{class Structure;}
namespace vk::commandbuffer{class Command_buffer;}
namespace vk::commandbuffer{class Allocator;}
namespace vk::synchro{class Semaphore;}
namespace vk::presentation{class Viewport;}
namespace vk::structure{class Fence;}
namespace vk::structure{class Render;}
namespace vk::structure{class Batch;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Command_buffer;}
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
  void record_all_renderpass(std::shared_ptr<vk::structure::Batch> batch);
  void record_renderpass(std::shared_ptr<vk::structure::Render> render);

  //Subfunction
  void prepare_renderpass(std::shared_ptr<vk::structure::Render> render);
  void start_renderpass(std::shared_ptr<vk::structure::Render> render);
  void draw_subpass(std::shared_ptr<vk::structure::Render> render);
  void stop_renderpass(std::shared_ptr<vk::structure::Render> render);
  void cmd_next_subset(std::shared_ptr<vk::structure::Render> render);
  void prepare_command(std::shared_ptr<vk::structure::Render> render);
  void cmd_viewport(std::shared_ptr<vk::structure::Render> render);

private:
  vk::Structure* vk_struct;
  vk::commandbuffer::Command_buffer* vk_command;
  vk::commandbuffer::Allocator* vk_allocator;
  vk::synchro::Semaphore* vk_semaphore;
  vk::presentation::Viewport* vk_viewport;
  sys::timer::Chrono* utl_chrono;
};

}
