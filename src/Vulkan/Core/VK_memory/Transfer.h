#pragma once

#include <vulkan/vulkan.h>
#include <memory>

namespace vk{class Structure;}
namespace vk::command{class Command;}
namespace vk::commandbuffer{class Command_buffer;}
namespace vk::commandbuffer{class Allocator;}
namespace vk::memory{class Transition;}
namespace vk::structure{class Image;}
namespace vk::structure{class Texture;}
namespace vk::structure{class Command_buffer;}
namespace vk::structure{class Buffer;}
namespace vk::structure{class Vertex;}


namespace vk::memory{

class Transfer
{
public:
  //Constructor / Destructor
  Transfer(vk::Structure* vk_struct);
  ~Transfer();

public:
  //Texture function
  void copy_texture_to_gpu(vk::structure::Texture& texture, void* data, VkImageLayout final_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  void copy_gpu_image_to_buffer(vk::structure::Image& image, VkBuffer buffer);
  void copy_gpu_depth_to_buffer(vk::structure::Image& image, VkBuffer buffer);
  void blit_gpu_image_to_gpu_image(vk::structure::Image& image_src, vk::structure::Image& image_dst);
  void copy_gpu_image_to_gpu_image_standalone(vk::structure::Image& image_src, vk::structure::Image& image_dst);
  std::shared_ptr<vk::structure::Command_buffer> copy_gpu_image_to_gpu_image(vk::structure::Image& image_src, vk::structure::Image& image_dst);

  //Vertex function
  void copy_vertex_to_gpu(vk::structure::Vertex& vertex, const void* data);

private:
  vk::Structure* vk_struct;
  vk::memory::Transition* vk_transition;
  vk::command::Command* vk_command;
  vk::commandbuffer::Command_buffer* vk_commandbuffer;
  vk::commandbuffer::Allocator* vk_allocator;
};

}
