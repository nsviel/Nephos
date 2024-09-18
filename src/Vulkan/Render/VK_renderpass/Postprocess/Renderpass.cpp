#include "Renderpass.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::render::edl{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_edl = new vk::render::edl::EDL(vk_struct);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Init function
void Renderpass::init(){
  //---------------------------

  vk::structure::Renderpass& renderpass = vk_struct->render.renderpass.edl;
  //vk::structure::Renderpass* renderpass = new vk::structure::Renderpass();
  this->create_renderpass(renderpass);
  vk_edl->create_subpass(renderpass);

  //---------------------------
}

//Init function
void Renderpass::create_renderpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  renderpass.name = "edl";
  vk_struct->render.renderpass.vec_renderpass.push_back(&renderpass);

  //---------------------------

}

}
