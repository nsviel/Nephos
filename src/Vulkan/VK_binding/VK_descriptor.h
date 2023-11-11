#ifndef VK_DESCRIPTOR_H
#define VK_DESCRIPTOR_H

#include <VK_struct/Struct_binding.h>
#include <VK_struct/Struct_framebuffer.h>
#include <VK_struct/Struct_pipeline.h>
#include <VK_struct/Struct_entity.h>
#include <VK_struct/Struct_renderpass.h>
#include <ELE_specific/common.h>

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
  void create_binding(Struct_binding* binding);
  void clean_binding(Struct_binding* binding);

  //Descriptor set update
  void update_descriptor_uniform(Struct_binding* binding);
  void update_descriptor_sampler(Struct_binding* binding, vector<Struct_image*> vec_image);
  void update_descriptor_sampler(Struct_binding* binding, Struct_image* image);

  //Subfunction
  void cmd_bind_descriptor(VkCommandBuffer& command_buffer, Struct_pipeline* pipeline, VkDescriptorSet set);
  void allocate_descriptor_set(Struct_binding* binding);
  void create_layout_from_required(Struct_binding* binding);
  VkDescriptorSetLayout create_layout(vector<VkDescriptorSetLayoutBinding>& vec_binding);

private:
  Struct_vulkan* struct_vulkan;
  VK_uniform* vk_uniform;
  VK_sampler* vk_sampler;
};

#endif
