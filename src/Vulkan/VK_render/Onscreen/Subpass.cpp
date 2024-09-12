#include "Subpass.h"

#include <Vulkan/Namespace.h>


namespace vk::render::onscreen{

//Constructor / Destructor
Subpass::Subpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_renderpass = new vk::renderpass::Renderpass(vk_struct);
  this->vk_pipeline = new vk::render::pipeline::Canvas(vk_struct);
  this->vk_imgui = new vk::gui::Imgui(vk_struct);

  //---------------------------
}
Subpass::~Subpass(){}

//Main function
void Subpass::create_subpass(vk::structure::Renderpass* renderpass){
  //---------------------------

  vk::structure::Subpass* subpass = new vk::structure::Subpass();
  subpass->target = vk::renderpass::PRESENTATION;
  subpass->draw_task = [this](vk::structure::Subpass* subpass){Subpass::draw(subpass);};

  vk_pipeline->add_pipeline_triangle(subpass);

  //---------------------------
  renderpass->vec_subpass.push_back(subpass);
}

//Subfunction
void Subpass::draw(vk::structure::Subpass* subpass){
  //---------------------------

  vk_imgui->draw_frame(subpass->command_buffer);

  //---------------------------
}

}
