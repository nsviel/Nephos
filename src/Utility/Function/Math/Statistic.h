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

Eigen::Matrix3f covariance(std::vector<Eigen::Vector3f>& vec);
Eigen::Matrix3d covariance(std::vector<Eigen::Vector3d>& vec);
float std(std::vector<float>& vec);
float var(std::vector<float>& vec);
float cv(std::vector<float>& vec);
float R2(std::vector<float>& data_X, std::vector<float>& data_Y, std::vector<float>& coeffs);

}
