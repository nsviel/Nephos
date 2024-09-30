#include "Renderpass.h"

#include <Vulkan/Namespace.h>


namespace vk::geometry{

//Constructor / Destructor
Renderpass::Renderpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_point = new vk::geometry::subpass::topology::Point(vk_struct);
  this->vk_line = new vk::geometry::subpass::topology::Line(vk_struct);
  this->vk_triangle = new vk::geometry::subpass::topology::Triangle(vk_struct);
  this->vk_dynamic_point = new vk::geometry::subpass::dynamic::Point(vk_struct);

  //---------------------------
}
Renderpass::~Renderpass(){}

//Main function
void Renderpass::init(){
  vk::structure::Renderpass& renderpass = vk_struct->graphics.render.renderpass.geometry;
  renderpass.attachment.target = vk::renderpass::SHADER;
  //---------------------------

  vk_point->create_subpass(renderpass);
  vk_line->create_subpass(renderpass);
  vk_triangle->create_subpass(renderpass);
  vk_dynamic_point->create_subpass(renderpass);

  //---------------------------
  vk_struct->graphics.render.renderpass.vec_renderpass.push_back(&renderpass);
}

}
