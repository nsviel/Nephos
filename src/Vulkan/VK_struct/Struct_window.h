#pragma once

#include <Utility/Specific/Common.h>


namespace vk::structure{

struct Window{
  //---------------------------

  //Window
  std::string title = "Nephos";
  GLFWwindow* handle = nullptr;

  //Dimension
  bool resized = false;
  glm::vec2 dimension =  glm::vec2(1024, 500);
  glm::vec2 constraint_min = glm::vec2(500, 250);
  glm::vec2 constraint_max = glm::vec2(4000, 4000);
  glm::vec2 center = glm::vec2(0, 0);
  VkExtent2D extent;
  VkSurfaceKHR surface;

  //---------------------------
};

}
