#pragma once

#include <Eigen/Dense>
#include <glm/glm.hpp>


namespace math{

//Distance functions
float distance(glm::vec3 pt1, glm::vec3 pt2);
float distance(Eigen::Vector3f pt1, Eigen::Vector3f pt2);
double distance(Eigen::Vector3d pt1, Eigen::Vector3d pt2);
double distance(Eigen::Vector4d pt1, Eigen::Vector4d pt2);
double distance(Eigen::Vector4d pt1, Eigen::Vector3d pt2);

double distance_from_origin(Eigen::Vector3d pt1);
float distance_from_origin(Eigen::Vector3f pt1);
float distance_from_origin(glm::vec3 pt1);

}
