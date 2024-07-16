#pragma once

#include <imgui/core/imgui.h>
#include <Eigen/Dense>
#include <glm/glm.hpp>
#include <vector>
#include <string>


namespace type{

void uint8_to_vec_uint8(const uint8_t* input, size_t size, std::vector<uint8_t>& output);
void uint8_to_vec_uint16(const uint8_t* input, size_t size, std::vector<uint16_t>& output);
float degree_to_radian(float degree);
float radian_to_degree(float radian);
glm::vec3 degree_to_radian(glm::vec3 degree);
glm::vec3 radian_to_degree_vec3(glm::vec3 radian);

}
