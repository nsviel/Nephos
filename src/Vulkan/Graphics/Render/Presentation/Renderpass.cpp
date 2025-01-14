#include "Renderpass.h"

#include <Vulkan/Namespace.h>


namespace vk::gfx::presentation{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_subpass = new vk::gfx::canvas::Subpass(vk_struct);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Main function
void Renderpass::init(){
  std::shared_ptr<vk::structure::Renderpass> renderpass = vk_struct->graphics.render.renderpass.presentation;
  if(vk_struct->interface.param.headless) return;
  //---------------------------

  renderpass->name = "Presentation";
  renderpass->attachment.target = vk::renderpass::PRESENTATION;

  vk_subpass->create_subpass(*renderpass);

  //---------------------------
  vk_struct->core.drawer.vec_renderpass.push_back(renderpass);
}

}
