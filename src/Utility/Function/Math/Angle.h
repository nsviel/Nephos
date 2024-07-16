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

float oriented_angle(glm::vec2 A, glm::vec2 B);
double angular_distance(const Eigen::Matrix3f& rota, const Eigen::Matrix3f& rotb);
std::vector<float> cross_product(std::vector<float>& vec_A, std::vector<float>& vec_B);
float dot_product(glm::vec3& vec_A, glm::vec3& vec_B);
float compute_cosIt(glm::vec3& xyz, glm::vec3& Nxyz, glm::vec3& root);
float compute_It(glm::vec3& xyz, glm::vec3& Nxyz, float& R);
glm::vec3 compute_normal_from_covariance(const glm::mat3& covariance);
void compute_normal_orientation(glm::vec3& normal, const glm::vec3& point);
float calculate_angle(const glm::vec3& v1, const glm::vec3& v2);
bool normal_same_sense(const glm::vec3& v1, const glm::vec3& v2);

}
