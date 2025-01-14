#include "Subpass.h"

#include <Vulkan/Namespace.h>


namespace vk::gfx::canvas{

//Constructor / Destructor
Subpass::Subpass(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_renderpass = new vk::renderpass::Renderpass(vk_struct);
  this->vk_triangle = new vk::geometry::pipeline::topology::Triangle(vk_struct);
  this->vk_imgui = new vk::gui::Imgui(vk_struct);

  //---------------------------
}
Subpass::~Subpass(){}

//Main function
void Subpass::create_subpass(vk::structure::Renderpass& renderpass){
  //---------------------------

  //Set subpass object
  std::shared_ptr<vk::structure::Subpass> subpass = std::make_shared<vk::structure::Subpass>();
  subpass->index = 0;
  subpass->source = VK_SUBPASS_EXTERNAL;
  subpass->draw_task = [this](vk::structure::Render& render){Subpass::draw_subpass(render);};

  //Set pipeline
  vk_triangle->add_pipeline(*subpass);

  //---------------------------
  renderpass.vec_subpass.push_back(subpass);
}
void Subpass::draw_subpass(vk::structure::Render& render){
  //---------------------------

  vk_imgui->draw_frame(*render.command_buffer);

  //---------------------------
}

}
