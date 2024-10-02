#include "Descriptor.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::geometry{

//Uniform
vk::structure::Descriptor uniform_mvp(){
  //---------------------------

  vk::structure::Descriptor descriptor;
  descriptor.name = "mvp";
  descriptor.size = sizeof(vk::geometry::MVP);
  descriptor.binding = vk::uniform::MVP;
  descriptor.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptor.stage = VK_SHADER_STAGE_VERTEX_BIT;

  //---------------------------
  return descriptor;
}
vk::structure::Descriptor uniform_point_size(){
  //---------------------------

  vk::structure::Descriptor descriptor;
  descriptor.name = "width";
  descriptor.size = sizeof(float);
  descriptor.binding = vk::uniform::TOPOLOGY_WIDTH;
  descriptor.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptor.stage = VK_SHADER_STAGE_VERTEX_BIT;

  //---------------------------
  return descriptor;
}

//Storage
vk::structure::Descriptor storage_cloud(){
  //---------------------------

  vk::structure::Descriptor descriptor;
  descriptor.name = "tex_cloud";
  descriptor.binding = vk::storage::CLOUD;
  descriptor.type = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
  descriptor.stage = VK_SHADER_STAGE_VERTEX_BIT;

  //---------------------------
  return descriptor;
}

}
