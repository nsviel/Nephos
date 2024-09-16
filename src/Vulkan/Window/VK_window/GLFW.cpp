#include "GLFW.h"

#include <Vulkan/Namespace.h>


namespace vk::window{

//Constructor / Destructor
GLFW::GLFW(vk::Structure* vk_struct){
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

  this->window_poll_event();
  this->window_close_event();

  //---------------------------
}
void GLFW::clean(){
  //---------------------------

  this->destroy_window();

  //---------------------------
}

//Window function
void GLFW::create_window(){
  if(vk_struct->render.param.headless) return;
  //---------------------------

  int width  = vk_struct->window.window.dimension.x;
  int height = vk_struct->window.window.dimension.y;
  std::string title = vk_struct->window.window.title;

  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  vk_struct->window.window.handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

  if(!glfwVulkanSupported()){
    printf("GLFW: Vulkan Not Supported\n");
    exit(0);
  }

  this->set_window_constraint_min(vk_struct->window.window.constraint_min);

  //---------------------------
}
void GLFW::destroy_window(){
  if(vk_struct->window.window.handle == nullptr) return;
  //---------------------------

  glfwDestroyWindow(vk_struct->window.window.handle);
  glfwTerminate();

  //---------------------------
}
void GLFW::create_surface(){
  if(vk_struct->window.window.handle == nullptr) return;
  //---------------------------

  this->update_window_dim();
  VkResult result = glfwCreateWindowSurface(vk_struct->core.instance.handle, vk_struct->window.window.handle, nullptr, &vk_struct->window.window.surface);
  if(result != VK_SUCCESS){
    throw std::runtime_error("[error] failed to create window surface!");
  }

  //---------------------------
}

//Sizing function
void GLFW::update_window_dim(){
  if(vk_struct->window.window.handle == nullptr) return;
  //---------------------------

  int width, height;
  glfwGetFramebufferSize(vk_struct->window.window.handle, &width, &height);

  vk_struct->window.window.dimension = glm::vec2(width, height);
  vk_struct->window.window.center = glm::vec2(width/2, height/2);

  //---------------------------
}
bool GLFW::is_window_resized(){
  //---------------------------

  int width, height;
  glfwGetFramebufferSize(vk_struct->window.window.handle, &width, &height);

  if(width != vk_struct->window.window.dimension.x || height != vk_struct->window.window.dimension.y){
    return true;
  }

  //---------------------------
  return false;
}
void GLFW::set_window_constraint_min(glm::vec2 constraint){
  if(vk_struct->window.window.handle == nullptr) return;
  //---------------------------

  glfwSetWindowSizeLimits(vk_struct->window.window.handle, constraint.x, constraint.y, GLFW_DONT_CARE, GLFW_DONT_CARE);

  //---------------------------
}
void GLFW::set_window_constraint_max(glm::vec2 constraint){
  if(vk_struct->window.window.handle == nullptr) return;
  //---------------------------

  glfwSetWindowSizeLimits(vk_struct->window.window.handle, GLFW_DONT_CARE, GLFW_DONT_CARE, constraint.x, constraint.y);

  //---------------------------
}

//Input function
void GLFW::wait_event(){
  if(vk_struct->window.window.handle == nullptr) return;
  //---------------------------

  glfwWaitEvents();

  //---------------------------
}
void GLFW::window_close_event(){
  if(vk_struct->window.window.handle == nullptr) return;
  //---------------------------

  bool window_closing = glfwWindowShouldClose(vk_struct->window.window.handle);
  if(window_closing) *vk_struct->window.window.running = false;

  //---------------------------
}
void GLFW::window_poll_event(){
  if(vk_struct->window.window.handle == nullptr) return;
  //---------------------------

  glfwPollEvents();

  //---------------------------
}
void GLFW::set_mouse_pose(glm::vec2 pose){
  if(vk_struct->window.window.handle == nullptr) return;
  //---------------------------

  glfwSetCursorPos(vk_struct->window.window.handle, pose.x, pose.y);

  //---------------------------
}
glm::vec2 GLFW::get_mouse_pose(){
  if(vk_struct->window.window.handle == nullptr) return glm::vec2(0, 0);
  //---------------------------

  double xpos, ypos;
  glfwGetCursorPos(vk_struct->window.window.handle, &xpos, &ypos);
  glm::vec2 pos = glm::vec2(xpos, ypos);

  //---------------------------
  return pos;
}
glm::vec2 GLFW::get_dimension(){
  return vk_struct->window.window.dimension;
}

}
