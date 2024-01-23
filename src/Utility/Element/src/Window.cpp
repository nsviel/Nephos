#include "Window.h"

#include <Config.h>


namespace utl::element{

//Constructor / Destructor
Window::Window(Config* config){
  //---------------------------

  this->config = config;
  this->has_been_resized = false;

  //---------------------------
}
Window::~Window(){}

//Main function
void Window::create_window(){
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
void Window::close_window(){
  //---------------------------

  glfwSetWindowShouldClose(window, true);

  //---------------------------
}
void Window::destroy_window(){
  //---------------------------

  glfwDestroyWindow(window);
  glfwTerminate();

  //---------------------------
}

//Subfunction
void Window::set_window_size_minimum(int width, int height){
  //---------------------------

  glfwSetWindowSizeLimits(window, width, height, GLFW_DONT_CARE, GLFW_DONT_CARE);

  //---------------------------
}
void Window::set_window_size_maximum(int width, int height){
  //---------------------------

  glfwSetWindowSizeLimits(window, GLFW_DONT_CARE, GLFW_DONT_CARE, width, height);

  //---------------------------
}

//Sizing function
void Window::manage_input(){
  //---------------------------

  glfwPollEvents();

  //---------------------------
}
vec2 Window::compute_window_dim(){
  vec2 dim = vec2(0);
  //---------------------------

  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  this->window_dim = vec2(width, height);
  this->window_center = glm::vec2(width/2, height/2);
/*
  std::cout<<("=====")<<std::endl;
  //say(mouse_pose);
  std::cout<<(window_center.x)<<std::endl;
  std::cout<<(window_center.y)<<std::endl;
*/
  //---------------------------
  return window_dim;
}
bool Window::check_for_resizing(){
  //---------------------------

  vec2 dim = compute_window_dim();
  if(dim.x != window_dim.x || dim.y != window_dim.y){
    this->has_been_resized = true;
    this->window_dim = dim;
  }

  //---------------------------
  return has_been_resized;
}
bool Window::window_should_close(){
  //---------------------------

  bool stop = glfwWindowShouldClose(window);
  config->run_app = !stop;

  //---------------------------
  return stop;
}

//Mouse position
glm::vec2 Window::get_mouse_pose(){
  //---------------------------

  double xpos, ypos;
  glfwGetCursorPos(window, &xpos, &ypos);
  glm::vec2 pos = glm::vec2(xpos, ypos);

  //---------------------------
  return pos;
}
void Window::set_mouse_pose(glm::vec2 pos){
  //---------------------------

  glfwSetCursorPos(window, pos.x, pos.y);

  //---------------------------
}

}
