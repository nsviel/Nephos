#include "Distance.h"


namespace math{

//Basic functions
float distance(glm::vec3 pt1, glm::vec3 pt2){
  //Euclidean distance
  float dist;
  //---------------------------

  dist = sqrt(pow(pt1.x - pt2.x,2) + pow(pt1.y - pt2.y,2) + pow(pt1.z - pt2.z,2));

  //---------------------------
  return dist;
}
float distance(Eigen::Vector3f pt1, Eigen::Vector3f pt2){
  //Euclidean distance
  //---------------------------

  float X = pt1(0) - pt2(0);
  float Y = pt1(1) - pt2(1);
  float Z = pt1(2) - pt2(2);

  float dist = sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2));

  //---------------------------
  return dist;
}
double distance(Eigen::Vector3d pt1, Eigen::Vector3d pt2){
  //Euclidean distance
  //---------------------------

  double X = pt1(0) - pt2(0);
  double Y = pt1(1) - pt2(1);
  double Z = pt1(2) - pt2(2);

  double dist = sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2));

  //---------------------------
  return dist;
}
double distance(Eigen::Vector4d pt1, Eigen::Vector4d pt2){
  //Euclidean distance
  //---------------------------

  double X = pt1(0) - pt2(0);
  double Y = pt1(1) - pt2(1);
  double Z = pt1(2) - pt2(2);

  double dist = sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2));

  //---------------------------
  return dist;
}
double distance(Eigen::Vector4d pt1, Eigen::Vector3d pt2){
  //Euclidean distance
  //---------------------------

  double X = pt1(0) - pt2(0);
  double Y = pt1(1) - pt2(1);
  double Z = pt1(2) - pt2(2);

  double dist = sqrt(pow(X, 2) + pow(Y, 2) + pow(Z, 2));

  //---------------------------
  return dist;
}

double distance_from_origin(Eigen::Vector3f pt1){
  //Euclidean distance
  double dist;
  //---------------------------

  dist = sqrt(pow(pt1(0), 2) + pow(pt1(1), 2) + pow(pt1(2), 2));

  //---------------------------
  return dist;
}
double distance_from_origin(glm::vec3 pt1){
  //Euclidean distance
  double dist;
  //---------------------------

  dist = sqrt(pow(pt1.x, 2) + pow(pt1.y, 2) + pow(pt1.z, 2));

  //---------------------------
  return dist;
}
double distance_from_origin(Eigen::Vector3d pt1){
  //Euclidean distance
  double dist;
  //---------------------------

  dist = sqrt(pow(pt1(0), 2) + pow(pt1(1), 2) + pow(pt1(2), 2));

  //---------------------------
  return dist;
}

}
