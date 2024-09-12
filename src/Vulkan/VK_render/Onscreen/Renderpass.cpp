#include "Renderpass.h"

#include <Vulkan/Namespace.h>


namespace vk::render::onscreen{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_subpass = new vk::render::onscreen::Subpass(vk_struct);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Main function
void Renderpass::init(){
  if(vk_struct->param.headless) return;
  //---------------------------

  vk::structure::Renderpass* renderpass = new vk::structure::Renderpass();
  this->create_renderpass(renderpass);
  vk_subpass->create_subpass(renderpass);

  //---------------------------
}

//Init function
void Renderpass::create_renderpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  renderpass->name = "gui";
  vk_struct->render.vec_renderpass.push_back(renderpass);

  //---------------------------
}

}
