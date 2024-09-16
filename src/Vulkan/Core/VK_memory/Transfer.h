#pragma once

#include <vulkan/vulkan.h>
#include <memory>

namespace vk::command{class Command_buffer;}
namespace vk::command{class Allocator;}
namespace vk::image{class Transition;}
namespace vk{class Structure;}
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
  void copy_buffer_to_image(vk::structure::Image& image, VkBuffer buffer);
  void copy_image_to_buffer(vk::structure::Image& image, VkBuffer buffer);
  void copy_image_to_image_standalone(vk::structure::Image& image_src, vk::structure::Image& image_dst);
  void blit_image_to_image(vk::structure::Image& image_src, vk::structure::Image& image_dst);
  std::shared_ptr<vk::structure::Command_buffer> copy_image_to_image(vk::structure::Image& image_src, vk::structure::Image& image_dst);

  //Data copy function
  void copy_data_to_gpu(vk::data::structure::Buffer& buffer, const void* data, VkDeviceSize dataSize);
  void copy_data_to_gpu(vk::data::structure::Buffer& buffer, vk::data::structure::Buffer& stagger, const void* data, VkDeviceSize dataSize);

private:
  vk::Structure* vk_struct;
  vk::image::Transition* vk_transition;
  vk::command::Command_buffer* vk_command_buffer;
  vk::command::Allocator* vk_command_allocator;
};

}
