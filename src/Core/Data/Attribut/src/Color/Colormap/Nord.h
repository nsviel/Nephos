#pragma once

#include <vector>
#include <glm/glm.hpp>


//Nord palette
//https://www.nordtheme.com/docs/colors-and-palettes
inline std::vector<glm::vec4> nordic_palette = {
  glm::vec4(0.180392, 0.203922, 0.25098, 1),   // Dark
  glm::vec4(0.231373, 0.258824, 0.321569, 1),  // Less dark
  glm::vec4(0.262745, 0.298039, 0.368627, 1),  // Less less dark
  glm::vec4(0.298039, 0.337255, 0.415686, 1),  // Less less less dark
  glm::vec4(0.847059, 0.870588, 0.913725, 1),  // Light gray
  glm::vec4(0.898039, 0.913725, 0.941176, 1),  // More light gray
  glm::vec4(0.92549, 0.937255, 0.956863, 1),   // More more light gray
  glm::vec4(0.560784, 0.737255, 0.733333, 1),  // Blue-green
  glm::vec4(0.533333, 0.752941, 0.815686, 1),  // Cyan
  glm::vec4(0.505882, 0.631373, 0.756863, 1),  // Light blue
  glm::vec4(0.368627, 0.505882, 0.67451, 1),   // Blue
  glm::vec4(0.74902, 0.380392, 0.415686, 1),   // Red
  glm::vec4(0.815686, 0.529412, 0.439216, 1),  // Orange
  glm::vec4(0.921569, 0.796078, 0.545098, 1),  // Yellow
  glm::vec4(0.639216, 0.745098, 0.54902, 1),   // Green
  glm::vec4(0.705882, 0.556863, 0.678431, 1)   // Purple
};
