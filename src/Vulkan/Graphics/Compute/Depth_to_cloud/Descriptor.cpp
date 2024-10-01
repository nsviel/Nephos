#include "Descriptor.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::compute::dtc{

//Sampler
vk::structure::Descriptor storage_depth(){
  //---------------------------

  vk::structure::Descriptor descriptor;
  descriptor.name = "tex_depth";
  descriptor.binding = vk::storage::DEPTH;
  descriptor.type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
  descriptor.stage = VK_SHADER_STAGE_COMPUTE_BIT;

  //---------------------------
  return descriptor;
}
vk::structure::Descriptor storage_tablexy(){
  //---------------------------

  vk::structure::Descriptor descriptor;
  descriptor.name = "tex_tablexy";
  descriptor.binding = vk::storage::TABLE_XY;
  descriptor.type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
  descriptor.stage = VK_SHADER_STAGE_COMPUTE_BIT;

  //---------------------------
  return descriptor;
}
vk::structure::Descriptor storage_cloud(){
  //---------------------------

  vk::structure::Descriptor descriptor;
  descriptor.name = "tex_cloud";
  descriptor.binding = vk::storage::CLOUD;
  descriptor.type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
  descriptor.stage = VK_SHADER_STAGE_COMPUTE_BIT;

  //---------------------------
  return descriptor;
}

}
