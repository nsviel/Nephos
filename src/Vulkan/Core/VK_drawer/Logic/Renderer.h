#pragma once

namespace vk::commandbuffer{class Command_buffer;}
namespace vk::commandbuffer{class Allocator;}
namespace vk{class Structure;}
namespace vk::structure{class Fence;}
namespace vk::structure{class Render;}
namespace vk::structure{class Renderpass;}
namespace vk::structure{class Command_buffer;}


namespace vk::draw{

class Renderer
{
public:
  //Constructor / Destructor
  Renderer(vk::Structure* vk_struct);
  ~Renderer();

public:
  //Main function
  void run_renderpass(vk::structure::Render& render);

  //Subfunction
  void start_renderpass(vk::structure::Render& render);
  void draw_subpass(vk::structure::Render& render);
  void stop_renderpass(vk::structure::Render& render);

private:
  vk::Structure* vk_struct;
  vk::commandbuffer::Command_buffer* vk_command;
  vk::commandbuffer::Allocator* vk_allocator;
};

}
