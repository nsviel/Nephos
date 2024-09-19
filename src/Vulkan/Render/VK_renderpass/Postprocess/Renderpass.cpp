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
  vk::structure::Renderpass& renderpass = vk_struct->render.renderpass.postprocess;
  renderpass.attachment.target = vk::renderpass::SHADER;
  //---------------------------

  vk_edl->create_subpass(renderpass);

  //---------------------------
  vk_struct->render.renderpass.vec_renderpass.push_back(&renderpass);
}

}
