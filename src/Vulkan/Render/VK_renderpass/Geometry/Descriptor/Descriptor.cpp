#include "Descriptor.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::geometry{

//Uniform
vk::descriptor::structure::Descriptor uniform_mvp(){
  //---------------------------

  vk::descriptor::structure::Descriptor descriptor;
  descriptor.name = "mvp";
  descriptor.size = sizeof(vk::geometry::MVP);
  descriptor.binding = vk::uniform::MVP;
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
  descriptor.binding = vk::uniform::TOPOLOGY_WIDTH;
  descriptor.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptor.stage = VK_SHADER_STAGE_VERTEX_BIT;

  //---------------------------
  return descriptor;
}
vk::descriptor::structure::Descriptor uniform_dynamic(){
  //---------------------------

  vk::descriptor::structure::Descriptor descriptor;
  descriptor.name = "DYN_param";
  descriptor.size = sizeof(vk::geometry::Dynamic);
  descriptor.binding = vk::uniform::PARAMETER;
  descriptor.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptor.stage = VK_SHADER_STAGE_VERTEX_BIT;

  //---------------------------
  return descriptor;
}

//Sampler
vk::descriptor::structure::Descriptor sampler_color(){
  //---------------------------

  vk::descriptor::structure::Descriptor descriptor;
  descriptor.name = "tex_color";
  descriptor.binding = vk::sampler::COLOR;
  descriptor.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  descriptor.stage = VK_SHADER_STAGE_VERTEX_BIT;

  //---------------------------
  return descriptor;
}
vk::descriptor::structure::Descriptor sampler_depth(){
  //---------------------------

  vk::descriptor::structure::Descriptor descriptor;
  descriptor.name = "tex_depth";
  descriptor.binding = vk::sampler::DEPTH;
  descriptor.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  descriptor.stage = VK_SHADER_STAGE_VERTEX_BIT;

  //---------------------------
  return descriptor;
}

}
