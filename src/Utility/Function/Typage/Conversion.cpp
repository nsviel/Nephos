#include "Casting.h"

#include <bits/stdc++.h>


namespace type{

void uint8_to_vec_uint8(const uint8_t* input, size_t size, std::vector<uint8_t>& output){
  //---------------------------

  output = std::vector<uint8_t>(input, input + size);

  //---------------------------
}
void uint8_to_vec_uint16(const uint8_t* input, size_t size, std::vector<uint16_t>& output){
  //---------------------------

  // Ensure the input size is even, as each uint16_t is 2 uint8_t
  if(size % 2 != 0){
    throw std::invalid_argument("[error] Input size must be even to convert to uint16_t.");
  }

  // Resize the output vector to hold the correct number of uint16_t values
  size_t outputSize = size / 2;
  output.resize(outputSize);

  // Convert each pair of uint8_t values into a single uint16_t value
  for(size_t i = 0; i < outputSize; ++i){
    output[i] = static_cast<uint16_t>(input[2 * i]) | (static_cast<uint16_t>(input[2 * i + 1]) << 8);
  }

  //---------------------------
}
float degree_to_radian(float degree){
  float radian;
  //---------------------------

  radian = degree * 3.14159265358979323846f / 180;

  //---------------------------
  return radian;
}
float radian_to_degree(float radian){
  float degree;
  //---------------------------

  degree = (radian * 180) / 3.14159265358979323846f;

  //---------------------------
  return degree;
}
glm::vec3 degree_to_radian(glm::vec3 degree){
  glm::vec3 radian;
  //---------------------------

  for(int i=0; i<3; i++){
    radian[i] = degree[i] * 3.14159265358979323846f / 180;
  }

  //---------------------------
  return radian;
}
glm::vec3 radian_to_degree_vec3(glm::vec3 radian){
  glm::vec3 degree;
  //---------------------------

  for(int i=0; i<3; i++){
    degree[i] = (radian[i] * 180) / 3.14159265358979323846f;
  }

  //---------------------------
  return degree;
}
std::string format_title(const std::string& name, int totalWidth){
  //---------------------------

  int nameLength = name.length();
  int dashLength = (totalWidth - nameLength - 2) / 2;
  if (totalWidth <= nameLength) return name;

  std::ostringstream ss;
  ss << std::string(dashLength, '-') << " " << name << " " << std::string(dashLength, '-');

  // Add any remaining dashes to ensure it reaches the total width
  int currentLength = ss.str().length();
  if (currentLength < totalWidth) {
    ss << std::string(totalWidth - currentLength, '-');
  }

  //---------------------------
  return ss.str();
}

}
