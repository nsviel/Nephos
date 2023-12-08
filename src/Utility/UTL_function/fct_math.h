#pragma once

#include <numeric>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include <algorithm>
#include <Eigen/Dense>
#include <math.h>

/**
 * \brief Basic math functions
 */

namespace math{

//Distance functions
float compute_distance(glm::vec3 pt1, glm::vec3 pt2);
float compute_distance_origin(Eigen::Vector3f pt1);
float compute_distance_origin(glm::vec3 pt1);
float compute_distance(Eigen::Vector3f pt1, Eigen::Vector3f pt2);
float dot_product(glm::vec3 vec_A, glm::vec3 vec_B);
float compute_sum(std::vector<float>& vec);
double compute_distance_origin(Eigen::Vector3d pt1);
double compute_distance(Eigen::Vector3d pt1, Eigen::Vector3d pt2);
double compute_distance(Eigen::Vector4d pt1, Eigen::Vector4d pt2);
double compute_distance(Eigen::Vector4d pt1, Eigen::Vector3d pt2);
bool is_nan(glm::vec3 vec);
bool is_nan(Eigen::Vector3d vec);

//Basic function
std::vector<float> compute_inv(std::vector<float>& vec);
std::vector<float> vector_ones(int size);
std::string thousand_separator(int n);
float sign(float value);

//Minimum / Mean / Maximum
int min_z_id(std::vector<glm::vec3> vec);
float mean(std::vector<float>& vec);
float mean_and_clear(std::vector<float>& vec);
float max(std::vector<float>& vec);
float max_vec(std::vector<std::vector<float>>& vec);
float min(std::vector<float>& vec);
int min(std::vector<int>& vec);
float min(float in1, float in2);

Eigen::Vector3f centroid(std::vector<Eigen::Vector3f>& XYZ);
Eigen::Vector3d centroid(std::vector<Eigen::Vector3d>& XYZ);
glm::vec2 min_vec2(std::vector<glm::vec2> XY);
glm::vec2 max_vec2(std::vector<glm::vec2> XY);
glm::vec3 centroid(std::vector<glm::vec3>& vec);
glm::vec3 centroid(glm::vec3& vec1, glm::vec3& vec2);
glm::vec3 max_vec3(std::vector<glm::vec3> XYZ);
glm::vec3 min_z(std::vector<glm::vec3> vec);
glm::vec3 min_vec3(std::vector<glm::vec3> XYZ);

//Normalization
std::vector<float> normalize(std::vector<float>& vec);
std::vector<double> normalize(std::vector<double>& vec);
std::vector<float> normalize(std::vector<float>& vec, glm::vec2 range);
std::vector<float> normalize(std::vector<float>& vec, float value_to_avoid);
std::vector<float> normalize_01(std::vector<float>& vec);
std::vector<float> cross_product(std::vector<float>& vec_A, std::vector<float>& vec_B);
std::vector<float> standardize(std::vector<float>& vec, float value_to_avoid);

//Statistical functions
float std(std::vector<float>& vec);
float var(std::vector<float>& vec);
float cv(std::vector<float>& vec);
float R2(std::vector<float>& data_X, std::vector<float>& data_Y, std::vector<float>& coeffs);
Eigen::Matrix3f covariance_matrix(std::vector<Eigen::Vector3f>& vec);
Eigen::Matrix3d covariance_matrix(std::vector<Eigen::Vector3d>& vec);

//Sorting functions
std::vector<size_t> sort_by_indexes(const std::vector<float> &v);
std::vector<size_t> sort_by_indexes_greater(const std::vector<float> &v);
bool is_number(const std::string& s);

//Geometric functions
float oriented_angle(glm::vec2 A, glm::vec2 B);
float degreeToRadian(float degree);
float radianToDegree(float radian);
double angularDistance(const Eigen::Matrix3f &rota, const Eigen::Matrix3f &rotb);
glm::vec3 degreeToRadian_vec3(glm::vec3 degree);
glm::vec3 radianToDegree_vec3(glm::vec3 radian);

}
