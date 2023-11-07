#include "ELE_window.h"

#include <../config.h>


//Constructor / Destructor
ELE_window::ELE_window(Config* config){
  //---------------------------

  this-> config = config;
  this->has_been_resized = false;

  //---------------------------
}
ELE_window::~ELE_window(){}

//Main function
void ELE_window::create_window(){
  //---------------------------

  int width  = config->window_dim.x;
  int height = config->window_dim.y;
  string title = config->window_title;

  glfwInit();
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  this->window_dim = glm::vec2(width, height);

  if (!glfwVulkanSupported()){
    printf("GLFW: Vulkan Not Supported\n");
    exit(0);
  }

  //---------------------------
}
void ELE_window::close_window(){
  //---------------------------

  glfwSetWindowShouldClose(window, true);

  //---------------------------
}
void ELE_window::destroy_window(){
  //---------------------------

  glfwDestroyWindow(window);
  glfwTerminate();

  //---------------------------
}

//Subfunction
void ELE_window::set_window_size_minimum(int width, int height){
  //---------------------------

  glfwSetWindowSizeLimits(window, width, height, GLFW_DONT_CARE, GLFW_DONT_CARE);

  //---------------------------
}
void ELE_window::set_window_size_maximum(int width, int height){
  //---------------------------

  glfwSetWindowSizeLimits(window, GLFW_DONT_CARE, GLFW_DONT_CARE, width, height);

  //---------------------------
}

//Sizing function
void ELE_window::manage_input(){
  //---------------------------

  glfwPollEvents();

  //---------------------------
}
vec2 ELE_window::compute_window_dim(){
  vec2 dim = vec2(0);
  //---------------------------

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  this->window_dim = vec2(width, height);
  this->window_center = glm::vec2(width/2, height/2);

  //---------------------------
  return window_dim;
}
bool ELE_window::check_for_resizing(){
  //---------------------------

  vec2 dim = compute_window_dim();
  if(dim.x != window_dim.x || dim.y != window_dim.y){
    this->has_been_resized = true;
    this->window_dim = dim;
  }

  //---------------------------
  return has_been_resized;
}
bool ELE_window::window_should_close(){
  //---------------------------

  return glfwWindowShouldClose(window);

  //---------------------------
}

//Mouse position
glm::vec2 ELE_window::get_mouse_pose(){
  //---------------------------

  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  glm::vec2 pos = glm::vec2(xpos, ypos);

  //---------------------------
  return pos;
}
void ELE_window::set_mouse_pose(glm::vec2 pos){
  //---------------------------

  glfwSetCursorPos(window, pos.x, pos.y);

  //---------------------------
}
