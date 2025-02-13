#include "Renderpass.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::postprocess{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_edl = new vk::gfx::edl::Subpass(vk_struct);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Init function
void Renderpass::init(){
  std::shared_ptr<vk::structure::Renderpass> renderpass = vk_struct->graphics.render.renderpass.postprocess;
  //---------------------------

  renderpass->name = "EDL";
  renderpass->attachment.target = vk::renderpass::SHADER;
  renderpass->with_screenshot = true;

  vk_edl->create_subpass(*renderpass);

  //---------------------------
  vk_struct->core.drawer.vec_renderpass.push_back(renderpass);
}

}
