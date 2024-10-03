#include "Canvas.h"

#include <Vulkan/Namespace.h>


namespace vk::present::subpass{

//Constructor / Destructor
Canvas::Canvas(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_renderpass = new vk::renderpass::Renderpass(vk_struct);
  this->vk_triangle = new vk::geometry::pipeline::topology::Triangle(vk_struct);
  this->vk_imgui = new vk::gui::Imgui(vk_struct);

  //---------------------------
}
Canvas::~Canvas(){}

//Main function
void Canvas::create_subpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  //Set subpass object
  std::shared_ptr<vk::structure::Subpass> subpass = std::make_shared<vk::structure::Subpass>();
  subpass->index = 0;
  subpass->source = VK_SUBPASS_EXTERNAL;
  subpass->draw_task = [this](vk::structure::Render& render){Canvas::draw_subpass(render);};

  //Set pipeline
  vk_triangle->add_pipeline(*subpass);

  //---------------------------
  renderpass.vec_subpass.push_back(subpass);
}
void Canvas::draw_subpass(vk::structure::Render& render){
  //---------------------------

  vk_imgui->draw_frame(*render.command_buffer);

  //---------------------------
}

}
