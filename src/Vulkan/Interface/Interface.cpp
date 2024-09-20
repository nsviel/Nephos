#include "Interface.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk{

//Constructor / Destructor
Interface::Interface(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_imgui = new vk::gui::Imgui(vk_struct);
  this->vk_window = new vk::window::Window(vk_struct);
  this->vk_texture = new vk::texture::Ressource(vk_struct);

  this->vk_screenshot = new vk::image::Screenshot(vk_struct);
  this->vk_data = new vk::data::Data(vk_struct);
  this->vk_texgui = new vk::gui::Texture(vk_struct);

  //---------------------------
}
Interface::~Interface(){}

//Data function
ImTextureID Interface::query_render_texture(){
  return vk_texgui->query_render_texture();
}
void Interface::insert_data(std::shared_ptr<utl::base::Data> data, std::shared_ptr<utl::base::Pose> pose){
  vk_data->insert(data, pose);
}
void Interface::remove_data(utl::base::Data& data){
  vk_data->remove(data);
}
void Interface::insert_texture(std::shared_ptr<utl::media::Image> image){
  vk_texture->insert_texture(image);
}
void Interface::insert_texture(utl::base::Data& data, std::shared_ptr<utl::media::Image> image){
  //vk_texture->insert_texture(data, image);
}
void Interface::insert_gui_texture(std::shared_ptr<utl::media::Image> image){
  vk_texgui->insert_texture(image);
}

//Window function
glm::vec2 Interface::get_mouse_pose(){
  return vk_window->get_mouse_pose();
}
glm::vec2 Interface::get_dimension(){
  return vk_window->get_dimension();
}
void Interface::set_mouse_pose(glm::vec2 pose){
  vk_window->set_mouse_pose(pose);
}
void Interface::make_screenshot(){
  vk_screenshot->make_screenshot();
}

//Camera
void Interface::set_mat_view(glm::mat4 mat){
  vk_struct->core.presentation.view = mat;
}
void Interface::set_mat_projection(glm::mat4 mat){
  vk_struct->core.presentation.projection = mat;
}

}
