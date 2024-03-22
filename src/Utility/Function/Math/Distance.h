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
float distance(glm::vec3 pt1, glm::vec3 pt2);
float distance(Eigen::Vector3f pt1, Eigen::Vector3f pt2);
double distance(Eigen::Vector3d pt1, Eigen::Vector3d pt2);
double distance(Eigen::Vector4d pt1, Eigen::Vector4d pt2);
double distance(Eigen::Vector4d pt1, Eigen::Vector3d pt2);

float distance_from_origin(Eigen::Vector3f pt1);
float distance_from_origin(glm::vec3 pt1);
double distance_from_origin(Eigen::Vector3d pt1);

}
