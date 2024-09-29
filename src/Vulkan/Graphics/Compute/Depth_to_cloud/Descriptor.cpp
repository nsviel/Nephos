#include "Descriptor.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::compute::dtc{

//Sampler
vk::structure::Descriptor sampler_depth(){
  //---------------------------

  vk::structure::Descriptor descriptor;
  descriptor.name = "tex_depth";
  descriptor.binding = vk::sampler::DEPTH;
  descriptor.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  descriptor.stage = VK_SHADER_STAGE_COMPUTE_BIT;

  //---------------------------
  return descriptor;
}
vk::structure::Descriptor sampler_table_xy(){
  //---------------------------

  vk::structure::Descriptor descriptor;
  descriptor.name = "tex_table_xy";
  descriptor.binding = vk::sampler::TABLE_XY;
  descriptor.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  descriptor.stage = VK_SHADER_STAGE_COMPUTE_BIT;

  //---------------------------
  return descriptor;
}
vk::structure::Descriptor sampler_storage_pc(){
  //---------------------------

  vk::structure::Descriptor descriptor;
  descriptor.name = "tex_cloud";
  descriptor.binding = vk::sampler::STORAGE;
  descriptor.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  descriptor.stage = VK_SHADER_STAGE_COMPUTE_BIT;

  //---------------------------
  return descriptor;
}

}
