#include "Render.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::interface{

//Constructor / Destructor
Render::Render(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_render = new vk::gui::Render(vk_struct);
  this->vk_retriever = new vk::data::Retriever(vk_struct);
  this->vk_imgui = new vk::gui::Imgui(vk_struct);
  this->vk_shader = new vk::shader::Reloader(vk_struct);

  //---------------------------
}
Render::~Render(){}

//Main function
void Render::draw_render_texture(glm::vec2 dimension){
  vk_render->display_image(vk_struct->graphics.render.presentation, dimension);
}
void Render::draw_depth_texture(glm::vec2 dimension){
  vk_render->display_image(vk_struct->graphics.render.depth, dimension);
}
void Render::draw_image(std::shared_ptr<utl::base::Image> image, glm::vec2 dimension){
  //---------------------------

  auto texture = vk_retriever->retrieve_vk_texture(*image);
  if(!texture) return;
  vk_render->display_image(*texture, dimension);

  //---------------------------
}
void Render::draw_image(utl::base::Data& data, std::shared_ptr<utl::base::Image> image, glm::vec2 dimension){
  //---------------------------

  //Retrieve data vk object
  auto vk_object = vk_retriever->retrieve_vk_object(data);
  if(!vk_object) return;

  //Check if image already inserted
  auto texture = vk_retriever->retrieve_vk_texture(*vk_object, image->name);
  if(!texture) return;

  //Display image texture
  vk_render->display_image(*texture, dimension);

  //---------------------------
}
void Render::reload_shader(){
  vk_shader->hot_shader_reload();
}
void Render::new_frame(){
  vk_imgui->new_frame();
}

}
