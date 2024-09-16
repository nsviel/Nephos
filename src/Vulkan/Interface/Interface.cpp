#include "Interface.h"

#include <Vulkan/Namespace.h>


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

//Main function
void Interface::set_mouse_pose(glm::vec2 pose){
  vk_window->set_mouse_pose(pose);
}
glm::vec2 Interface::get_mouse_pose(){
  return vk_window->get_mouse_pose();
}
glm::vec2 Interface::get_dimension(){
  return vk_window->get_dimension();
}

}
