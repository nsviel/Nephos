#include "Window.h"

#include <Vulkan/Namespace.h>


namespace vk::window{

//Constructor / Destructor
Window::Window(vk::Structure* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
Window::~Window(){}

//Main function
void Window::create_window(){
  if(vk_struct->interface.param.headless) return;
  //---------------------------

  int width  = vk_struct->window.dimension.x;
  int height = vk_struct->window.dimension.y;
  std::string title = vk_struct->window.title;

  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  vk_struct->window.handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

  if(!glfwVulkanSupported()){
    printf("GLFW: Vulkan Not Supported\n");
    exit(0);
  }

  this->set_window_constraint_min(vk_struct->window.constraint_min);

  //---------------------------
}
void Window::destroy_window(){
  if(vk_struct->window.handle == nullptr) return;
  //---------------------------

  glfwDestroyWindow(vk_struct->window.handle);
  glfwTerminate();

  //---------------------------
}
void Window::create_surface(){
  if(vk_struct->window.handle == nullptr) return;
  //---------------------------

  this->update_window_dim();
  VkResult result = glfwCreateWindowSurface(vk_struct->core.instance.handle, vk_struct->window.handle, nullptr, &vk_struct->window.surface);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create window surface!");
  }

  //---------------------------
}

//Subfunction
void Window::update_window_dim(){
  if(vk_struct->window.handle == nullptr) return;
  //---------------------------

  int width, height;
  glfwGetFramebufferSize(vk_struct->window.handle, &width, &height);

  vk_struct->window.dimension = glm::vec2(width, height);
  vk_struct->window.center = glm::vec2(width/2, height/2);

  //---------------------------
}
bool Window::is_window_resized(){
  //---------------------------

  int width, height;
  glfwGetFramebufferSize(vk_struct->window.handle, &width, &height);

  if(width != vk_struct->window.dimension.x || height != vk_struct->window.dimension.y){
    return true;
  }

  //---------------------------
  return false;
}
void Window::set_window_constraint_min(glm::vec2 constraint){
  if(vk_struct->window.handle == nullptr) return;
  //---------------------------

  glfwSetWindowSizeLimits(vk_struct->window.handle, constraint.x, constraint.y, GLFW_DONT_CARE, GLFW_DONT_CARE);

  //---------------------------
}
void Window::set_window_constraint_max(glm::vec2 constraint){
  if(vk_struct->window.handle == nullptr) return;
  //---------------------------

  glfwSetWindowSizeLimits(vk_struct->window.handle, GLFW_DONT_CARE, GLFW_DONT_CARE, constraint.x, constraint.y);

  //---------------------------
}
void Window::set_mouse_pose(glm::vec2 pose){
  if(vk_struct->window.handle == nullptr) return;
  //---------------------------

  glfwSetCursorPos(vk_struct->window.handle, pose.x, pose.y);

  //---------------------------
}
glm::vec2 Window::get_mouse_pose(){
  if(vk_struct->window.handle == nullptr) return glm::vec2(0, 0);
  //---------------------------

  double xpos, ypos;
  glfwGetCursorPos(vk_struct->window.handle, &xpos, &ypos);
  glm::vec2 pos = glm::vec2(xpos, ypos);

  //---------------------------
  return pos;
}
glm::vec2 Window::get_dimension(){
  return vk_struct->window.dimension;
}

}
