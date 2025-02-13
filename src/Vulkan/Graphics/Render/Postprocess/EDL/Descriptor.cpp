#include "Descriptor.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::gfx::edl{

//Uniform
vk::structure::Descriptor uniform_edl(){
  //---------------------------

  vk::structure::Descriptor descriptor;
  descriptor.name = "parameter";
  descriptor.size = sizeof(vk::gfx::edl::Structure);
  descriptor.binding = vk::uniform::PARAMETER;
  descriptor.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptor.stage = VK_SHADER_STAGE_FRAGMENT_BIT;

  //---------------------------
  return descriptor;
}

//Sampler
vk::structure::Descriptor sampler_color(){
  //---------------------------

  vk::structure::Descriptor descriptor;
  descriptor.name = "tex_color";
  descriptor.binding = vk::sampler::COLOR;
  descriptor.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  descriptor.stage = VK_SHADER_STAGE_FRAGMENT_BIT;

  //---------------------------
  return descriptor;
}
vk::structure::Descriptor sampler_depth(){
  //---------------------------

  vk::structure::Descriptor descriptor;
  descriptor.name = "tex_depth";
  descriptor.binding = vk::sampler::DEPTH;
  descriptor.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  descriptor.stage = VK_SHADER_STAGE_FRAGMENT_BIT;

  //---------------------------
  return descriptor;
}

}
