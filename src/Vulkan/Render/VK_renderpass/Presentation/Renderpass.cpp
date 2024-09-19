#include "Renderpass.h"

#include <Vulkan/Namespace.h>


namespace vk::render::onscreen{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_subpass = new vk::render::onscreen::Canvas(vk_struct);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Main function
void Renderpass::init(){
  vk::structure::Renderpass& renderpass = vk_struct->render.renderpass.presentation;
  renderpass.target = vk::renderpass::PRESENTATION;
  if(vk_struct->param.headless) return;
  //---------------------------

  vk_subpass->create_subpass(renderpass);

  //---------------------------
  vk_struct->render.renderpass.vec_renderpass.push_back(&renderpass);
}

}
