#include "GLFW.h"

#include <Vulkan/Namespace.h>


namespace vk::window{

//Constructor / Destructor
GLFW::GLFW(vk::structure::Vulkan* vk_struct){
  //---------------------------

  this->vk_struct = vk_struct;

  //---------------------------
}
GLFW::~GLFW(){}

//Main function
void GLFW::init(){
  //---------------------------

  this->create_window();

  //---------------------------
}
void GLFW::loop(){
  //---------------------------

  this->window_input();
  this->window_closing();

  //---------------------------
}
void GLFW::clean(){
  //---------------------------

  this->destroy_window();

  //---------------------------
}

//Window function
void GLFW::create_window(){
  if(vk_struct->param.headless) return;
  //---------------------------

  int width  = vk_struct->window.dimension.x;
  int height = vk_struct->window.dimension.y;
  string title = vk_struct->window.title;

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
void GLFW::close_window(){
  if(vk_struct->window.handle == nullptr) return;
  //---------------------------

  glfwSetWindowShouldClose(vk_struct->window.handle, true);

  //---------------------------
}
void GLFW::destroy_window(){
  if(vk_struct->window.handle == nullptr) return;
  //---------------------------

  glfwDestroyWindow(vk_struct->window.handle);
  glfwTerminate();

  //---------------------------
}
bool GLFW::window_closing(){
  if(vk_struct->window.handle == nullptr) return false;
  //---------------------------

  bool closing = glfwWindowShouldClose(vk_struct->window.handle);
  if(closing) *vk_struct->window.running = false;

  //---------------------------
  return closing;
}
void GLFW::create_surface(){
  if(vk_struct->window.handle == nullptr) return;
  //---------------------------

  this->update_window_dim();
  VkResult result = glfwCreateWindowSurface(vk_struct->instance.handle, vk_struct->window.handle, nullptr, &vk_struct->window.surface);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create window surface!");
  }

  //---------------------------
}

//Sizing function
void GLFW::update_window_dim(){
  if(vk_struct->window.handle == nullptr) return;
  //---------------------------

  int width, height;
  glfwGetFramebufferSize(vk_struct->window.handle, &width, &height);

  vk_struct->window.dimension = vec2(width, height);
  vk_struct->window.center = glm::vec2(width/2, height/2);

  //---------------------------
}
bool GLFW::is_window_resized(){
  //---------------------------

  int width, height;
  glfwGetFramebufferSize(vk_struct->window.handle, &width, &height);

  if(width != vk_struct->window.dimension.x || height != vk_struct->window.dimension.y){
    return true;
  }

  //---------------------------
  return false;
}
void GLFW::set_window_constraint_min(glm::vec2 constraint){
  if(vk_struct->window.handle == nullptr) return;
  //---------------------------

  glfwSetWindowSizeLimits(vk_struct->window.handle, constraint.x, constraint.y, GLFW_DONT_CARE, GLFW_DONT_CARE);

  //---------------------------
}
void GLFW::set_window_constraint_max(glm::vec2 constraint){
  if(vk_struct->window.handle == nullptr) return;
  //---------------------------

  glfwSetWindowSizeLimits(vk_struct->window.handle, GLFW_DONT_CARE, GLFW_DONT_CARE, constraint.x, constraint.y);

  //---------------------------
}

//Input function
void GLFW::wait_event(){
  if(vk_struct->window.handle == nullptr) return;
  //---------------------------

  glfwWaitEvents();

  //---------------------------
}
void GLFW::window_input(){
  if(vk_struct->window.handle == nullptr) return;
  //---------------------------

  glfwPollEvents();

  //---------------------------
}
void GLFW::set_mouse_pose(glm::vec2 pose){
  if(vk_struct->window.handle == nullptr) return;
  //---------------------------

  glfwSetCursorPos(vk_struct->window.handle, pose.x, pose.y);

  //---------------------------
}
glm::vec2 GLFW::get_mouse_pose(){
  if(vk_struct->window.handle == nullptr) return vec2(0, 0);
  //---------------------------

  double xpos, ypos;
  glfwGetCursorPos(vk_struct->window.handle, &xpos, &ypos);
  glm::vec2 pos = glm::vec2(xpos, ypos);

  //---------------------------
  return pos;
}
glm::vec2 GLFW::get_dimension(){
  return vk_struct->window.dimension;
}

}
