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

// Min
int min(std::vector<int>& vec);
float min(std::vector<float>& vec);
float min(float in1, float in2);
glm::vec2 min(std::vector<glm::vec2> XY);
glm::vec3 min(std::vector<glm::vec3> XYZ);

// Max
float max(std::vector<float>& vec);
float max(std::vector<std::vector<float>>& vec);
glm::vec2 max(std::vector<glm::vec2> XY);
glm::vec3 max(std::vector<glm::vec3> XYZ);

// Centroid
glm::vec3 centroid(std::vector<glm::vec3>& vec);
glm::vec3 centroid(glm::vec3& vec1, glm::vec3& vec2);
Eigen::Vector3f centroid(std::vector<Eigen::Vector3f>& XYZ);
Eigen::Vector3d centroid(std::vector<Eigen::Vector3d>& XYZ);
glm::vec3 centroid(const std::vector<glm::vec3>& vec);

// Operation
float sum(std::vector<float>& vec);
float mean(std::vector<float>& vec);
void divise(std::vector<float>& vec, int diviser);
std::vector<size_t> sort_by_index(const std::vector<float> &v);
std::vector<size_t> sort_by_index_greater(const std::vector<float> &v);
std::vector<float> inv(std::vector<float>& vec);

//Normalization
void normalize(std::vector<float>& vec);
void normalize(std::vector<float>& vec, glm::vec2 range);
void normalize(std::vector<float>& vec, float value_to_avoid);
void normalize(std::vector<float>& vec, glm::vec2 range, glm::vec2 clamp);

//Checker
bool is_nan(glm::vec3 vec);
bool is_nan(Eigen::Vector3d vec);
bool is_number(const std::string& s);

//Misc
double ceil(double value, int decimalPlaces);
double truncate(double value, int decimalPlaces);
float sign(float value);
glm::vec4 random();
glm::vec4 random(int seed);
std::string thousand_separator(int n);

}
