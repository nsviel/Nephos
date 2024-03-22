#pragma once

#include <numeric>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include <algorithm>
#include <Eigen/Dense>
#include <math.h>


namespace math{

//Operation
void divise(std::vector<float>& vec, int diviser);
std::vector<size_t> sort_by_index(const std::vector<float> &v);
std::vector<size_t> sort_by_index_greater(const std::vector<float> &v);
std::vector<float> inv(std::vector<float>& vec);

//Normalization
void normalize(std::vector<float>& vec);
void normalize(std::vector<float>& vec, glm::vec2 range);
void normalize(std::vector<float>& vec, float value_to_avoid);
std::vector<float> standardize(std::vector<float>& vec, float value_to_avoid);

//Conversion
float degree_to_radian(float degree);
float radian_to_degree(float radian);
glm::vec3 degree_to_radian(glm::vec3 degree);
glm::vec3 radian_to_degree_vec3(glm::vec3 radian);

//Checker
bool is_nan(glm::vec3 vec);
bool is_nan(Eigen::Vector3d vec);
bool is_number(const std::string& s);

//Misc
float sign(float value);
glm::vec4 random();
glm::vec4 random(int seed);
std::string thousand_separator(int n);

}
