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
void Type::uniform_point_size(vk::structure::Descriptor_required& descriptor){
  //---------------------------

  descriptor = {};
  descriptor.name = "point_size";
  descriptor.size = sizeof(int);
  descriptor.binding = 1;
  descriptor.type = TYP_UNIFORM;
  descriptor.stage = TYP_SHADER_VS;

  //---------------------------
}
void Type::uniform_mvp(vk::structure::Descriptor_required& descriptor){
  //---------------------------

  descriptor = {};
  descriptor.name = "mvp";
  descriptor.size = sizeof(mat4);
  descriptor.binding = 0;
  descriptor.type = TYP_UNIFORM;
  descriptor.stage = TYP_SHADER_VS;

  //---------------------------
}
void Type::sampler_color(vk::structure::Descriptor_required& descriptor){
  //---------------------------

  descriptor = {};
  descriptor.name = "tex_color";
  descriptor.size = 0;
  descriptor.binding = 1;
  descriptor.type = TYP_IMAGE_SAMPLER;
  descriptor.stage = TYP_SHADER_FS;

  //---------------------------
}



}
