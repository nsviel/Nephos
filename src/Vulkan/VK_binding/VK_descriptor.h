#pragma once

#include <VK_struct/Struct_vk_binding.h>
#include <VK_struct/Struct_vk_pipeline.h>
#include <VK_struct/Namespace.h>
#include <VK_struct/Struct_vk_renderpass.h>
#include <UTL_specific/common.h>

class Struct_vulkan;
class VK_uniform;
class VK_sampler;


class VK_descriptor
{
public:
  //Constructor / Destructor
  VK_descriptor(Struct_vulkan* struct_vulkan);
  ~VK_descriptor();

public:
  //Main functions
  void create_binding(Struct_vk_binding* binding);
  void clean_binding(Struct_vk_binding* binding);

  //Descriptor set update
  void update_descriptor_uniform(Struct_vk_binding* binding);
  void update_descriptor_sampler(Struct_vk_binding* binding, vector<vk::structure::Image*> vec_image);
  void update_descriptor_sampler(Struct_vk_binding* binding, vk::structure::Image* image);

  //Subfunction
  void cmd_bind_descriptor(VkCommandBuffer& command_buffer, Struct_vk_pipeline* pipeline, VkDescriptorSet set);
  void allocate_descriptor_set(Struct_vk_binding* binding);
  void create_layout_from_required(Struct_vk_binding* binding);
  VkDescriptorSetLayout create_layout(vector<VkDescriptorSetLayoutBinding>& vec_binding);

private:
  Struct_vulkan* struct_vulkan;
  VK_uniform* vk_uniform;
  VK_sampler* vk_sampler;
};
