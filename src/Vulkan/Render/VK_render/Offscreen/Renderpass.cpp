#include "Renderpass.h"

#include <Vulkan/Namespace.h>


namespace vk::render::offscreen{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_scene = new vk::render::offscreen::Scene(vk_struct);
  this->vk_edl = new vk::render::offscreen::EDL(vk_struct);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Main function
void Renderpass::init(){
  vk::structure::Renderpass& renderpass = vk_struct->renderpass.offscreen;
  //---------------------------

  vk_scene->create_subpass(renderpass);
  //vk_edl->create_subpass(renderpass);

  //---------------------------
  vk_struct->renderpass.vector.push_back(&renderpass);
}

}
