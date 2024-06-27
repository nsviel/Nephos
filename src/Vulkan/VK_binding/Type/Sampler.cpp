#include "Sampler.h"

#include <Vulkan/Namespace.h>


namespace vk::binding{

//Constructor / Destructor
Sampler::Sampler(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Sampler::~Sampler(){}

//Main function
void Sampler::create_sampler(vk::binding::structure::Binding* binding){
  binding->vec_sampler.clear();
  //---------------------------

  std::vector<vk::structure::Descriptor_required>& vec_required = binding->vec_required_binding;
  std::vector<vk::binding::structure::Sampler*>& vec_sampler = binding->vec_sampler;

  for(int i=0; i<vec_required.size(); i++){
    vk::structure::Descriptor_required& descriptor = vec_required[i];

    if(descriptor.type == TYP_IMAGE_SAMPLER || descriptor.type == VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE){
      vk::binding::structure::Sampler* sampler = create_sampler_obj(descriptor.name, descriptor.binding, descriptor.type);
      vec_sampler.push_back(sampler);
    }
  }

  //---------------------------
}
vk::binding::structure::Sampler* Sampler::create_sampler_obj(std::string name, int binding, VkDescriptorType type){
  vk::binding::structure::Sampler* sampler = new vk::binding::structure::Sampler();
  //---------------------------

  sampler->name = name;
  sampler->binding = binding;
  sampler->type = type;

  //---------------------------
  return sampler;
}

//Subfunction
vk::structure::Descriptor_required Sampler::sampler_color(){
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
vk::structure::Descriptor_required Sampler::sampler_depth(){
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
