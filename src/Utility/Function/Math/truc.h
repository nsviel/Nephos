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

// Mean
float mean(std::vector<float>& vec);

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

// Operation
float sum(std::vector<float>& vec);


// Centroid
glm::vec3 centroid(std::vector<glm::vec3>& vec);
glm::vec3 centroid(glm::vec3& vec1, glm::vec3& vec2);
Eigen::Vector3f centroid(std::vector<Eigen::Vector3f>& XYZ);
Eigen::Vector3d centroid(std::vector<Eigen::Vector3d>& XYZ);

// Covariance
Eigen::Matrix3f covariance(std::vector<Eigen::Vector3f>& vec);
Eigen::Matrix3d covariance(std::vector<Eigen::Vector3d>& vec);

// Statistic stuff
float std(std::vector<float>& vec);
float var(std::vector<float>& vec);
float cv(std::vector<float>& vec);
float R2(std::vector<float>& data_X, std::vector<float>& data_Y, std::vector<float>& coeffs);

}
