#include "Renderpass.h"

#include <Vulkan/Namespace.h>


namespace vk::present{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_subpass = new vk::present::subpass::Canvas(vk_struct);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Main function
void Renderpass::init(){
  vk::structure::Renderpass& renderpass = vk_struct->render.renderpass.presentation;
  renderpass.attachment.target = vk::renderpass::PRESENTATION;
  if(vk_struct->interface.param.headless) return;
  //---------------------------

  vk_subpass->create_subpass(renderpass);

  //---------------------------
  vk_struct->render.renderpass.vec_renderpass.push_back(&renderpass);
}

}
