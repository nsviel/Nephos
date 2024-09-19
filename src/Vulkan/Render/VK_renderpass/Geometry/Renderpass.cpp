#include "Renderpass.h"

#include <Vulkan/Namespace.h>


namespace vk::render::geometry{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_subpass = new vk::render::geometry::Subpass(vk_struct);
  this->vk_point = new vk::render::geometry::Point(vk_struct);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Main function
void Renderpass::init(){
  vk::structure::Renderpass& renderpass = vk_struct->render.renderpass.geometry;
  renderpass.target = vk::renderpass::SHADER;
  //---------------------------

  vk_subpass->create_subpass(renderpass);
  //vk_point->create_subpass(renderpass);

  //---------------------------
  vk_struct->render.renderpass.vec_renderpass.push_back(&renderpass);
}

}
