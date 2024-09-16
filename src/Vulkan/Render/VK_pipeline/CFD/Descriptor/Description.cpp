#include "Description.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::pipeline::cfd{

//Uniform
vk::binding::structure::Descriptor uniform_mvp(){
  //---------------------------

  vk::binding::structure::Descriptor descriptor;
  descriptor.name = "mvp";
  descriptor.size = sizeof(glm::mat4);
  descriptor.binding = vk::uniform::MVP;
  descriptor.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptor.stage = VK_SHADER_STAGE_VERTEX_BIT;

  //---------------------------
  return descriptor;
}
vk::binding::structure::Descriptor uniform_point_size(){
  //---------------------------

  vk::binding::structure::Descriptor descriptor;
  descriptor.name = "point_size";
  descriptor.size = sizeof(float);
  descriptor.binding = vk::uniform::WIDTH;
  descriptor.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptor.stage = VK_SHADER_STAGE_VERTEX_BIT;

  //---------------------------
  return descriptor;
}
vk::binding::structure::Descriptor uniform_cfd(){
  //---------------------------

  vk::binding::structure::Descriptor descriptor;
  descriptor.name = "EDL_param";
  descriptor.size = sizeof(vk::pipeline::cfd::Structure);
  descriptor.binding = vk::uniform::EDL;
  descriptor.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptor.stage = VK_SHADER_STAGE_FRAGMENT_BIT;

  //---------------------------
  return descriptor;
}

//Sampler
vk::binding::structure::Descriptor sampler_color(){
  //---------------------------

  vk::binding::structure::Descriptor descriptor;
  descriptor.name = "tex_color";
  descriptor.binding = vk::sampler::COLOR;
  descriptor.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  descriptor.stage = VK_SHADER_STAGE_FRAGMENT_BIT;

  //---------------------------
  return descriptor;
}
vk::binding::structure::Descriptor sampler_depth(){
  //---------------------------

  vk::binding::structure::Descriptor descriptor;
  descriptor.name = "tex_depth";
  descriptor.binding = vk::sampler::DEPTH;
  descriptor.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  descriptor.stage = VK_SHADER_STAGE_FRAGMENT_BIT;

  //---------------------------
  return descriptor;
}

}
