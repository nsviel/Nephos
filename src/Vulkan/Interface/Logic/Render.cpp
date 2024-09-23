#include "Render.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::interface{

//Constructor / Destructor
Render::Render(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_render = new vk::gui::Render(vk_struct);
  this->vk_data = new vk::data::Function(vk_struct);

  //---------------------------
}
Render::~Render(){}

//Main function
void Render::draw_render_texture(glm::vec2 dimension){
  vk_render->display_image(vk_struct->render.presentation.texture, dimension);
}
void Render::draw_image(std::shared_ptr<utl::media::Image> image, glm::vec2 dimension){
  //---------------------------

  auto texture = vk_data->retrieve_vk_texture(*image);
  if(!texture) return;
  vk_render->display_image(*texture, dimension);

  //---------------------------
}

}
