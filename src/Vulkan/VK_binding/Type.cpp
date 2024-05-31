#include "Type.h"

#include <Vulkan/Namespace.h>


namespace vk::binding{

//Constructor / Destructor
Type::Type(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Type::~Type(){}

//Main function
vk::structure::Descriptor_required Type::uniform_point_size(){
  //---------------------------

  vk::structure::Descriptor_required descriptor;
  descriptor.name = "point_size";
  descriptor.size = sizeof(int);
  descriptor.binding = 1;
  descriptor.type = TYP_UNIFORM;
  descriptor.stage = TYP_SHADER_VS;

  //---------------------------
  return descriptor;
}
vk::structure::Descriptor_required Type::uniform_mvp(){
  //---------------------------

  vk::structure::Descriptor_required descriptor;
  descriptor.name = "mvp";
  descriptor.size = sizeof(mat4);
  descriptor.binding = 0;
  descriptor.type = TYP_UNIFORM;
  descriptor.stage = TYP_SHADER_VS;

  //---------------------------
  return descriptor;
}
vk::structure::Descriptor_required Type::uniform_edl(){
  //---------------------------

  vk::structure::Descriptor_required descriptor;
  descriptor.name = "EDL_param";
  descriptor.size = sizeof(vk::render::edl::Structure);
  descriptor.binding = 5;
  descriptor.type = TYP_UNIFORM;
  descriptor.stage = TYP_SHADER_FS;

  //---------------------------
  return descriptor;
}
vk::structure::Descriptor_required Type::sampler_color(){
  //---------------------------

  vk::structure::Descriptor_required descriptor;
  descriptor.name = "tex_color";
  descriptor.size = 0;
  descriptor.binding = 1;
  descriptor.type = TYP_IMAGE_SAMPLER;
  descriptor.stage = TYP_SHADER_FS;

  //---------------------------
  return descriptor;
}
vk::structure::Descriptor_required Type::sampler_depth(){
  //---------------------------

  vk::structure::Descriptor_required descriptor;
  descriptor.name = "tex_depth";
  descriptor.size = 0;
  descriptor.binding = 4;
  descriptor.type = TYP_IMAGE_SAMPLER;
  descriptor.stage = TYP_SHADER_FS;

  //---------------------------
  return descriptor;
}


}
