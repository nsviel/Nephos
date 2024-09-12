#include "Canvas.h"

#include <Vulkan/Namespace.h>


namespace vk::render::onscreen{

//Constructor / Destructor
Canvas::Canvas(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_renderpass = new vk::renderpass::Renderpass(vk_struct);
  this->vk_factory = new vk::render::pipeline::Factory(vk_struct);
  this->vk_imgui = new vk::gui::Imgui(vk_struct);

  //---------------------------
}
Canvas::~Canvas(){}

//Main function
void Canvas::create_subpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->target = vk::renderpass::PRESENTATION;
  subpass->draw_task = [this](vk::structure::Subpass* subpass){Canvas::draw(*subpass);};

  vk_factory->add_pipeline_triangle(*subpass);

  //---------------------------
  renderpass.vec_subpass.push_back(subpass);
}
void Canvas::draw_subpass(vk::structure::Subpass& subpass){
  //---------------------------

  vk_imgui->draw_frame(subpass.command_buffer);

  //---------------------------
}

}
