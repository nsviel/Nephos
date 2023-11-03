#ifndef VK_DESCRIPTOR_H
#define VK_DESCRIPTOR_H

#include "../VK_struct/struct_binding.h"
#include "../VK_struct/struct_frame.h"
#include "../VK_struct/struct_pipeline.h"
#include "../VK_struct/struct_data.h"
#include "../VK_struct/struct_renderpass.h"
#include <ELE_specific/common.h>

class VK_engine;
class struct_vulkan;
class VK_error;


class VK_descriptor
{
public:
  //Constructor / Destructor
  VK_descriptor(VK_engine* vk_engine);
  ~VK_descriptor();

public:
  //Main functions
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
  struct_vulkan* vk_struct;
  VK_error* vk_error;

  VkDescriptorPool descriptor_pool;
  int pool_nb_uniform;
  int pool_nb_sampler;
  int pool_nb_descriptor;
};

#endif
