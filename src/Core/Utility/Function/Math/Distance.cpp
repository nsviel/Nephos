#include "Distance.h"


namespace math{

//Basic functions
float distance(const glm::vec3& pt1, const glm::vec3& pt2){
  float dx = pt1.x - pt2.x;
  float dy = pt1.y - pt2.y;
  float dz = pt1.z - pt2.z;
  return std::sqrt(dx * dx + dy * dy + dz * dz);
}
float distance(const Eigen::Vector3f& pt1, const Eigen::Vector3f& pt2){
  return (pt1 - pt2).norm();
}
double distance(const Eigen::Vector3d& pt1, const Eigen::Vector3d& pt2){
  return (pt1 - pt2).norm();
}
double distance(const Eigen::Vector4d& pt1, const Eigen::Vector4d& pt2){
  Eigen::Vector3d diff = pt1.head<3>() - pt2.head<3>();
  return diff.norm();
}
double distance(const Eigen::Vector4d& pt1, const Eigen::Vector3d& pt2){
  Eigen::Vector3d diff = pt1.head<3>() - pt2;
  return diff.norm();
}

double distance_from_origin(const glm::vec3& pt1){
  //Euclidean distance
  //---------------------------

  return std::sqrt(pt1.x * pt1.x + pt1.y * pt1.y + pt1.z * pt1.z);

  //---------------------------
}
double distance_from_origin(const Eigen::Vector3f& pt1){
  return pt1.norm();
}
double distance_from_origin(const Eigen::Vector3d& pt1){
  return pt1.norm();
}

}
