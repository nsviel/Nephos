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
glm::vec3 centroid(const std::vector<glm::vec3>& vec);
float dot_product(glm::vec3& vec_A, glm::vec3& vec_B);
float compute_cosIt(glm::vec3& xyz, glm::vec3& Nxyz, glm::vec3& root);
float compute_It(glm::vec3& xyz, glm::vec3& Nxyz, float& R);

//Normalization
void normalize(std::vector<float>& vec);
void normalize(std::vector<float>& vec, glm::vec2 range);
void normalize(std::vector<float>& vec, float value_to_avoid);
void normalize(std::vector<float>& vec, glm::vec2 range, glm::vec2 clamp);
void compute_mean_and_std(const std::vector<float>& vec, float& mean, float& std);
std::vector<float> standardize(std::vector<float>& vec, float value_to_avoid);

//Normal
glm::mat3 compute_covariance(const std::vector<glm::vec3>& points);
glm::vec3 compute_normal_from_covariance(const glm::mat3& covariance);
void compute_normal_orientation(glm::vec3& normal, const glm::vec3& point);
float calculate_angle(const glm::vec3& v1, const glm::vec3& v2);
bool normal_same_sense(const glm::vec3& v1, const glm::vec3& v2);

//Conversion


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
