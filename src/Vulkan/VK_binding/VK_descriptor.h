#ifndef VK_DESCRIPTOR_H
#define VK_DESCRIPTOR_H

#include <VK_struct/Struct_binding.h>
#include <VK_struct/Struct_framebuffer.h>
#include <VK_struct/Struct_pipeline.h>
#include <VK_struct/Struct_data.h>
#include <VK_struct/Struct_renderpass.h>
#include <ELE_specific/common.h>

class VK_engine;
class Struct_vulkan;


class VK_descriptor
{
public:
  //Constructor / Destructor
  VK_descriptor(VK_engine* vk_engine);
  ~VK_descriptor();

public:
  //Main functions
  void cmd_bind_descriptor(Struct_renderpass* renderpass, string pipeline_name, VkDescriptorSet set);
  void clean_descriptor_pool();

  //Descriptor set allocation
  void allocate_descriptor_set(Struct_binding* binding);

  //Descriptor set update
  void update_descriptor_uniform(Struct_binding* binding);
  void update_descriptor_sampler(Struct_binding* binding, vector<Struct_image*> vec_image);
  void update_descriptor_sampler(Struct_binding* binding, Struct_image* image);

  //Descriptor layout
  void create_layout_from_required(Struct_binding* binding);
  VkDescriptorSetLayout create_layout(vector<VkDescriptorSetLayoutBinding>& vec_binding);
  VkDescriptorSetLayoutBinding add_descriptor_binding(VkDescriptorType type, VkShaderStageFlagBits stage, int count, int binding);

  //Descriptor pool
  void create_descriptor_pool();
  VkDescriptorPoolSize add_descriptor_type(VkDescriptorType type, int count);

private:
  VK_engine* vk_engine;
  Struct_vulkan* struct_vulkan;
};

#endif
