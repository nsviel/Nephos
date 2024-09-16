#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>


namespace vk::structure{

struct Window{
  //---------------------------

  //Window
  std::string title = "Nephos";
  GLFWwindow* handle = nullptr;
  bool headless = false;

  //Dimension
  VkExtent2D extent = {};
  VkSurfaceKHR surface = VK_NULL_HANDLE;
  glm::vec2 dimension =  glm::vec2(1024, 500);
  glm::vec2 constraint_min = glm::vec2(500, 250);
  glm::vec2 constraint_max = glm::vec2(4000, 4000);
  glm::vec2 center = glm::vec2(0, 0);
  bool resizing = false;
  bool* running = nullptr;
  int cpt = 0;

  //---------------------------
};

struct Panel{
  //---------------------------

  glm::vec2 dimension =  glm::vec2(1024, 500);
  glm::vec2 center = glm::vec2(0, 0);

  //---------------------------
};

}
