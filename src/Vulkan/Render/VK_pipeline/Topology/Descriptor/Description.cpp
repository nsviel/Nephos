#include "Description.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::pipeline::topology{

//Uniform
vk::descriptor::structure::Descriptor uniform_mvp(){
  //---------------------------

  vk::descriptor::structure::Descriptor descriptor;
  descriptor.name = "mvp";
  descriptor.size = sizeof(glm::mat4);
  descriptor.binding = vk::uniform::MVP;
  descriptor.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptor.stage = VK_SHADER_STAGE_VERTEX_BIT;

  //---------------------------
  return descriptor;
}
vk::descriptor::structure::Descriptor uniform_mvp_str(){
  //---------------------------

  vk::descriptor::structure::Descriptor descriptor;
  descriptor.name = "mvp_str";
  descriptor.size = sizeof(vk::pipeline::topology::Structure);
  descriptor.binding = vk::uniform::MVP_STR;
  descriptor.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptor.stage = VK_SHADER_STAGE_VERTEX_BIT;

  //---------------------------
  return descriptor;
}
vk::descriptor::structure::Descriptor uniform_point_size(){
  //---------------------------

  vk::descriptor::structure::Descriptor descriptor;
  descriptor.name = "point_size";
  descriptor.size = sizeof(float);
  descriptor.binding = vk::uniform::WIDTH;
  descriptor.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptor.stage = VK_SHADER_STAGE_VERTEX_BIT;

  //---------------------------
  return descriptor;
}

}
