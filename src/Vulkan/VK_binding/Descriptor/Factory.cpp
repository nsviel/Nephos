#include "Factory.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::binding{

//Uniform
vk::binding::structure::Descriptor uniform_mvp(){
  //---------------------------

  vk::binding::structure::Descriptor descriptor;
  descriptor.name = "mvp";
  descriptor.size = sizeof(glm::mat4);
  descriptor.binding = vk::binding::id::MVP;
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
  descriptor.binding = vk::binding::id::WIDTH;
  descriptor.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptor.stage = VK_SHADER_STAGE_VERTEX_BIT;

  //---------------------------
  return descriptor;
}
vk::binding::structure::Descriptor uniform_edl(){
  //---------------------------

  vk::binding::structure::Descriptor descriptor;
  descriptor.name = "EDL_param";
  descriptor.size = sizeof(vk::render::structure::EDL);
  descriptor.binding = vk::binding::id::EDL;
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
  descriptor.binding = 1;
  descriptor.type = TYP_IMAGE_SAMPLER;
  descriptor.stage = TYP_SHADER_FS;

  //---------------------------
  return descriptor;
}
vk::binding::structure::Descriptor sampler_depth(){
  //---------------------------

  vk::binding::structure::Descriptor descriptor;
  descriptor.name = "tex_depth";
  descriptor.binding = 4;
  descriptor.type = TYP_IMAGE_SAMPLER;
  descriptor.stage = TYP_SHADER_FS;

  //---------------------------
  return descriptor;
}

}
