#include "Renderpass.h"

#include <Vulkan/Namespace.h>


namespace vk::render::geometry{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_point = new vk::render::topology::Point(vk_struct);
  this->vk_line = new vk::render::topology::Line(vk_struct);
  this->vk_triangle = new vk::render::topology::Triangle(vk_struct);
  this->vk_dynamic_point = new vk::render::dynamic::Point(vk_struct);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Main function
void Renderpass::init(){
  vk::structure::Renderpass& renderpass = vk_struct->render.renderpass.geometry;
  renderpass.attachment.target = vk::renderpass::SHADER;
  //---------------------------

  vk_point->create_subpass(renderpass);
  vk_line->create_subpass(renderpass);
  vk_triangle->create_subpass(renderpass);
  vk_dynamic_point->create_subpass(renderpass);

  //---------------------------
  vk_struct->render.renderpass.vec_renderpass.push_back(&renderpass);
}

}
