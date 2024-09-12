#include "EDL.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::render::edl{

//Constructor / Destructor
EDL::EDL(vk::Structure* vk_struct, vk::render::edl::Shader* vk_shader){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_shader = vk_shader;
  this->vk_uniform = new vk::binding::Uniform(vk_struct);
  this->vk_sampler = new vk::binding::Sampler(vk_struct);
  this->vk_drawer = new vk::render::edl::Drawer(vk_struct, vk_shader);
  this->vk_factory = new vk::render::pipeline::Factory(vk_struct);
  
  //---------------------------
}
EDL::~EDL(){}

//Init function
void EDL::create_subpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->target = vk::renderpass::SHADER;
  subpass->draw_task = [this](vk::structure::Subpass* subpass){vk_drawer->draw_edl(subpass);};

  vk_factory->create_pipeline_edl(subpass);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}

}
