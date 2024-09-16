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
  vk::structure::Renderpass& renderpass = vk_struct->render.renderpass.onscreen;
  if(vk_struct->render.param.headless) return;
  //---------------------------

  vk_subpass->create_subpass(renderpass);

  //---------------------------
  vk_struct->render.renderpass.vector.push_back(&renderpass);
}

}
