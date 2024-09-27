#pragma once

#include <vulkan/vulkan.h>

namespace vk{class Structure;}
namespace vk::draw{class Renderer;}
namespace vk::synchro{class Fence;}
namespace vk::synchro{class Semaphore;}
namespace vk::structure{class Object;}


namespace vk::data{

class Vertex
{
public:
  //Constructor / Destructor
  Vertex(vk::Structure* vk_struct);
  ~Vertex();

public:
  //Main function
  void cmd_draw_vertex(VkCommandBuffer& command_buffer, vk::structure::Object& vk_object);
  void cmd_line_with(VkCommandBuffer& command_buffer, vk::structure::Object& vk_object);

protected:
  vk::Structure* vk_struct;
  vk::draw::Renderer* vk_render;
  vk::synchro::Fence* vk_fence;
  vk::synchro::Semaphore* vk_semaphore;
};

}