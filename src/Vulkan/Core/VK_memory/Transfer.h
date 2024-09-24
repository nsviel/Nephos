#pragma once

#include <vulkan/vulkan.h>
#include <memory>

namespace vk{class Structure;}
namespace vk::command{class Command;}
namespace vk::command{class Allocator;}
namespace vk::memory{class Transition;}
namespace vk::structure{class Image;}
namespace vk::structure{class Texture;}
namespace vk::structure{class Command_buffer;}
namespace vk::data::structure{class Buffer;}


namespace vk::memory{

class Transfer
{
public:
  //Constructor / Destructor
  Transfer(vk::Structure* vk_struct);
  ~Transfer();

public:
  //Image copy function
  void copy_texture_to_gpu(vk::structure::Texture& texture);
  void copy_image_to_gpu(vk::structure::Image& image, VkBuffer buffer);
  void copy_gpu_image_to_buffer(vk::structure::Image& image, VkBuffer buffer);
  void blit_gpu_image_to_gpu_image(vk::structure::Image& image_src, vk::structure::Image& image_dst);
  void copy_gpu_image_to_gpu_image_standalone(vk::structure::Image& image_src, vk::structure::Image& image_dst);
  std::shared_ptr<vk::structure::Command_buffer> copy_gpu_image_to_gpu_image(vk::structure::Image& image_src, vk::structure::Image& image_dst);

  //Data copy function
  void copy_vertex_to_gpu(vk::data::structure::Buffer& buffer, const void* data, VkDeviceSize dataSize);
  void copy_vertex_to_gpu(vk::data::structure::Buffer& buffer, vk::data::structure::Buffer& stagger, const void* data, VkDeviceSize dataSize);

private:
  vk::Structure* vk_struct;
  vk::memory::Transition* vk_transition;
  vk::command::Command* vk_command;
  vk::command::Allocator* vk_command_allocator;
};

}
