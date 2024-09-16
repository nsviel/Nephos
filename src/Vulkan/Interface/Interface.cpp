#include "Interface.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk{

//Constructor / Destructor
Interface::Interface(vk::Structure* vk_struct){
  //---------------------------

  this->vk_imgui = new vk::gui::Imgui(vk_struct);
  this->vk_window = new vk::window::GLFW(vk_struct);
  this->vk_texture = new vk::image::Texture(vk_struct);
  this->vk_screenshot = new vk::image::Screenshot(vk_struct);
  this->vk_data = new vk::data::Data(vk_struct);

  //---------------------------
}
Interface::~Interface(){}

//Data function
ImTextureID Interface::query_engine_texture(){
  return vk_imgui->query_engine_texture();
}
void Interface::insert_data(std::shared_ptr<utl::base::Data> data, std::shared_ptr<utl::base::Pose> pose){
  vk_data->insert(data, pose);
}
void Interface::remove_data(utl::base::Data& data){
  vk_data->remove(data);
}
void Interface::insert_texture(std::shared_ptr<utl::media::Image> utl_image){
  vk_texture->insert_texture(utl_image);
}
void Interface::load_texture(std::shared_ptr<utl::media::Image> utl_image){
  vk_imgui->load_texture(utl_image);
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

}
