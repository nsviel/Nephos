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

void compute_mean_and_std(const std::vector<float>& vec, float& mean, float& std);
glm::mat3 compute_covariance(const std::vector<glm::vec3>& points);
Eigen::Matrix3f covariance(std::vector<Eigen::Vector3f>& vec);
Eigen::Matrix3d covariance(std::vector<Eigen::Vector3d>& vec);
float std(std::vector<float>& vec);
float var(std::vector<float>& vec);
float cv(std::vector<float>& vec);
float R2(std::vector<float>& data_X, std::vector<float>& data_Y, std::vector<float>& coeffs);
std::vector<float> standardize(std::vector<float>& vec, float value_to_avoid);

}
