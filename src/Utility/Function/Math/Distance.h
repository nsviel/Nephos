#pragma once

#include <Eigen/Dense>
#include <glm/glm.hpp>


namespace math{

//Distance functions
float distance(const glm::vec3& pt1, const glm::vec3& pt2);
float distance(const Eigen::Vector3f pt1, const Eigen::Vector3f pt2);
double distance(const Eigen::Vector3d pt1, const Eigen::Vector3d pt2);
double distance(const Eigen::Vector4d& pt1, const Eigen::Vector4d& pt2);
double distance(const Eigen::Vector4d& pt1, const Eigen::Vector3d& pt2);

double distance_from_origin(const glm::vec3& pt1);
double distance_from_origin(const Eigen::Vector3d& pt1);
double distance_from_origin(const Eigen::Vector3f& pt1);


}
