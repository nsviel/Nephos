#include "Angle.h"

#include <Utility/Function/Math/Distance.h>
#include <random>


namespace math{

float oriented_angle(glm::vec2 A, glm::vec2 B){
  //---------------------------

  float det = A.x * B.y - A.y * B.x;
  float dot = A.x * B.x + A.y * B.y;
  float angle = atan2(det, dot);

  //---------------------------
  return angle;
}
double angular_distance(const Eigen::Matrix3f &rota, const Eigen::Matrix3f &rotb){
  //---------------------------

  double norm = ((rota * rotb.transpose()).trace() - 1) / 2;
  norm = std::acos(norm) * 180 / M_PI;

  //---------------------------
  return norm;
}
std::vector<float> cross_product(std::vector<float>& vec_A, std::vector<float>& vec_B){
  std::vector<float> vec_cross;
  //---------------------------

  vec_cross[0] = vec_A[1] * vec_B[2] - vec_A[2] * vec_B[1];
  vec_cross[1] = vec_A[2] * vec_B[0] - vec_A[0] * vec_B[2];
  vec_cross[2] = vec_A[0] * vec_B[1] - vec_A[1] * vec_B[0];

  //---------------------------
  return vec_cross;
}
float dot_product(glm::vec3& vec_A, glm::vec3& vec_B){
  float product = 0;
  //---------------------------

  // Loop for calculate cot product
  for(int i=0; i<3; i++){
    product = product + vec_A[i] * vec_B[i];
  }

  //---------------------------
  return product;
}
float compute_cosIt(glm::vec3& xyz, glm::vec3& Nxyz, glm::vec3& root){
  //---------------------------

  //Compute cosIt
  float cIt = 0;
  float dist = math::distance(xyz, root);
  for(int j=0; j<3; j++){
    cIt = cIt + ( -Nxyz[j] * ( (xyz[j] - root[j]) / dist ));
  }

  //Check for orientation
  if(cIt < 0){
    cIt = -cIt;
  }
  //Check for computability
  if(cIt >= 1){
    cIt = 0.9999;
  }

  //---------------------------
  return cIt;
}
float compute_It(glm::vec3& xyz, glm::vec3& Nxyz, float& R){
  //---------------------------

  //Compute cosIt
  float cIt = 0;
  glm::vec3 root = glm::vec3(0, 0, 0);
  for(int j=0; j<3; j++){
    cIt = cIt + ( -Nxyz[j] * ( (xyz[j] - root[j]) / R ));
  }

  //Check for orientation
  if(cIt < 0){
    cIt = -cIt;
  }
  //Check for computability
  if(cIt >= 1){
    cIt = 0.9999;
  }

  float It = acos(cIt) * 180 / M_PI;

  //---------------------------
  return It;
}
glm::vec3 compute_normal_from_covariance(const glm::mat3& covariance){
  //---------------------------

  // Convert glm::mat3 to Eigen::Matrix3f
  Eigen::Matrix3f eigenCovariance;
  for(int i = 0; i < 3; ++i){
    for(int j = 0; j < 3; ++j){
      eigenCovariance(i, j) = covariance[i][j];
    }
  }

  // Calculate the eigenvalues and eigenvectors of the covariance matrix
  Eigen::SelfAdjointEigenSolver<Eigen::Matrix3f> eigensolver(eigenCovariance);
  Eigen::Vector3f eigenvalues = eigensolver.eigenvalues();
  Eigen::Matrix3f eigenvectors = eigensolver.eigenvectors();

  // The eigenvector corresponding to the smallest eigenvalue represents the normal
  Eigen::Vector3f normalEigen = eigenvectors.col(0);

  // Convert Eigen::Vector3f to glm::vec3
  glm::vec3 normal(normalEigen[0], normalEigen[1], normalEigen[2]);

  //---------------------------
  return normal;
}
void compute_normal_orientation(glm::vec3& normal, const glm::vec3& point){
  //---------------------------

  // Check orientation towards the origin
  glm::vec3 centroid(0.0f); // Assuming the origin is (0, 0, 0)
  float dotProduct = glm::dot(normal, centroid - point);
  if(dotProduct < 0.0f){
    // Invert the normal
    normal = -normal;
  }

  //---------------------------
}
float calculate_angle(const glm::vec3& v1, const glm::vec3& v2){
  //---------------------------

  // Ensure both vectors are normalized
  glm::vec3 norm_v1 = glm::normalize(v1);
  glm::vec3 norm_v2 = glm::normalize(v2);

  // Calculate the dot product
  float dot_product = glm::dot(norm_v1, norm_v2);

  // Clamp the dot product to avoid numerical errors that might push the value outside [-1, 1]
  dot_product = glm::clamp(dot_product, -1.0f, 1.0f);

  // Calculate the angle in radians using acos
  float angle = acos(dot_product);

  //---------------------------
  return angle;
}
bool normal_same_sense(const glm::vec3& v1, const glm::vec3& v2){
  //---------------------------

  float dot = glm::dot(v1, v2);

  //---------------------------
  return dot > 0;
}

}
