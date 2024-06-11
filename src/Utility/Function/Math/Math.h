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
glm::vec3 centroid(std::vector<glm::vec3>& vec);
float dot_product(glm::vec3& vec_A, glm::vec3& vec_B);
float compute_cosIt(glm::vec3& xyz, glm::vec3& Nxyz, glm::vec3& root);
float compute_It(glm::vec3& xyz, glm::vec3& Nxyz, glm::vec3 root);

//Normalization
void normalize(std::vector<float>& vec);
void normalize(std::vector<float>& vec, glm::vec2 range);
void normalize(std::vector<float>& vec, float value_to_avoid);
std::vector<float> standardize(std::vector<float>& vec, float value_to_avoid);

//Normal
glm::mat3 compute_covariance(const std::vector<glm::vec3>& points);
glm::vec3 compute_normal_from_covariance(const glm::mat3& covariance);
void compute_normal_orientation(glm::vec3& normal, const glm::vec3& point);

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
double ceil(double value, int decimalPlaces);
double truncate(double value, int decimalPlaces);
float sign(float value);
glm::vec4 random();
glm::vec4 random(int seed);
std::string thousand_separator(int n);

}
