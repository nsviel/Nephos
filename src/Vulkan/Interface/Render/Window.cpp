#include "Window.h"

#include <Vulkan/Namespace.h>
#include <Utility/Namespace.h>


namespace vk::interface{

//Constructor / Destructor
Window::Window(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;
  this->vk_window = new vk::window::Window(vk_struct);
  this->vk_screenshot = new vk::screenshot::Export(vk_struct);

  //---------------------------
}
Window::~Window(){}

//Main function
glm::vec2 Window::get_mouse_pose(){
  return vk_window->get_mouse_pose();
}
glm::vec2 Window::get_window_dimension(){
  return vk_window->get_dimension();
}
void Window::set_mouse_pose(glm::vec2 pose){
  vk_window->set_mouse_pose(pose);
}
void Window::make_screenshot_color(){
  vk_screenshot->make_screenshot_color();
}
void Window::make_screenshot_depth(){
  vk_screenshot->make_screenshot_depth();
}
void Window::set_mat_view(glm::mat4 mat){
  vk_struct->core.presentation.view = mat;
}
void Window::set_mat_projection(glm::mat4 mat){
  vk_struct->core.presentation.projection = mat;
}
bool Window::is_running(){
  return vk_struct->window.running;
}

}
