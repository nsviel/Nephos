#include "Description.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::pipeline::edl{

//Uniform
vk::descriptor::structure::Descriptor uniform_edl(){
  //---------------------------

  vk::descriptor::structure::Descriptor descriptor;
  descriptor.name = "EDL_param";
  descriptor.size = sizeof(vk::pipeline::edl::Structure);
  descriptor.binding = vk::uniform::EDL;
  descriptor.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  descriptor.stage = VK_SHADER_STAGE_FRAGMENT_BIT;

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
  descriptor.stage = VK_SHADER_STAGE_FRAGMENT_BIT;

  //---------------------------
  return descriptor;
}
vk::descriptor::structure::Descriptor sampler_depth(){
  //---------------------------

  vk::descriptor::structure::Descriptor descriptor;
  descriptor.name = "tex_depth";
  descriptor.binding = vk::sampler::DEPTH;
  descriptor.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  descriptor.stage = VK_SHADER_STAGE_FRAGMENT_BIT;

  //---------------------------
  return descriptor;
}

}
