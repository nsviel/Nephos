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

  this->manage_input();
  this->window_should_close();
  this->check_for_resizing();

  //---------------------------
}
void GLFW::clean(){
  //---------------------------

  this->destroy_window();

  //---------------------------
}

//Window function
void GLFW::create_window(){
  //---------------------------

  int width  = vk_struct->window.dimension.x;
  int height = vk_struct->window.dimension.y;
  string title = vk_struct->window.title;

  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  vk_struct->window.handle = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  vk_struct->window.dimension = glm::vec2(width, height);

  if(!glfwVulkanSupported()){
    printf("GLFW: Vulkan Not Supported\n");
    exit(0);
  }

  //---------------------------
}
void GLFW::close_window(){
  //---------------------------

  glfwSetWindowShouldClose(vk_struct->window.handle, true);

  //---------------------------
}
void GLFW::destroy_window(){
  //---------------------------

  glfwDestroyWindow(vk_struct->window.handle);
  glfwTerminate();

  //---------------------------
}
bool GLFW::window_should_close(){
  //---------------------------

  bool stop = glfwWindowShouldClose(vk_struct->window.handle);
  //config->run_app = !stop;

  //---------------------------
  return stop;
}

//Sizing function
vec2 GLFW::compute_window_dim(){
  vec2 dim = vec2(0);
  //---------------------------

  int width, height;
  glfwGetFramebufferSize(vk_struct->window.handle, &width, &height);
  vk_struct->window.dimension = vec2(width, height);
  vk_struct->window.center = glm::vec2(width/2, height/2);

  //---------------------------
  return vk_struct->window.dimension;
}
bool GLFW::check_for_resizing(){
  vk_struct->window.resized = false;
  //---------------------------

  vec2 dim = compute_window_dim();
  if(dim.x != vk_struct->window.dimension.x || dim.y != vk_struct->window.dimension.y){
    vk_struct->window.resized = true;
    vk_struct->window.dimension = dim;
  }

  //---------------------------
  return vk_struct->window.resized;
}
void GLFW::set_window_constraint_min(int width, int height){
  //---------------------------

  glfwSetWindowSizeLimits(vk_struct->window.handle, width, height, GLFW_DONT_CARE, GLFW_DONT_CARE);

  //---------------------------
}
void GLFW::set_window_constraint_max(int width, int height){
  //---------------------------

  glfwSetWindowSizeLimits(vk_struct->window.handle, GLFW_DONT_CARE, GLFW_DONT_CARE, width, height);

  //---------------------------
}

//Input function
void GLFW::manage_input(){
  //---------------------------

  glfwPollEvents();

  //---------------------------
}
glm::vec2 GLFW::get_mouse_pose(){
  //---------------------------

  double xpos, ypos;
  glfwGetCursorPos(vk_struct->window.handle, &xpos, &ypos);
  glm::vec2 pos_1 = glm::vec2(xpos, ypos);

  //---------------------------
  return pos;
}
glm::vec2 GLFW::get_dimension(){
  return vk_struct->window.dimension;
}
glm::vec2 GLFW::get_center(){
  return vk_struct->window.center;
}
void GLFW::set_center(glm::vec2 value){
  vk_struct->window.center = value;
}
void GLFW::set_mouse_pose(glm::vec2 pos){
  //---------------------------

  glfwSetCursorPos(vk_struct->window.handle, pos.x, pos.y);

  //---------------------------
}

}
