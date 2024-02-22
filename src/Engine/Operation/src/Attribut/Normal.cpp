#include "Normal.h"

#include <Engine/Operation/Namespace.h>
#include <cstdlib>


namespace ope{

// Constructor / Destructor
Normal::Normal(){
  //---------------------------


  //---------------------------
}
Normal::~Normal(){}

//Main function
void Normal::compute_normal_from_grid(utl::type::Data* data){
  if(data->point.xyz.size() == 0) return;
  if(data->width == -1 || data->height == -1) return;
  //---------------------------

  //Prepare data
  vector<vec3> Nxyz(data->point.xyz.size(), vec3(0.0f));
  vec3 empty = vec3(0, 0, 0);
  float threshold = 0.5f;

  //Loop
  bool toggle = true;
  #pragma omp parallel for collapse(2) schedule(static)
  for(int i=0; i<data->height - 1; i++){
    for(int j=0; j<data->width - 1; j+=2){
      // Calculate the indices of the three points
      int index_1, index_2, index_3;
      if(toggle){
        index_1 = i * data->width + j;
        index_3 = index_1 + 1;
        index_2 = (i + 1) * data->width + j;
      } else {
        index_1 = i * data->width + j;
        index_2 = index_1 + 1;
        index_3 = (i - 1) * data->width + j + 1;
      }

      const vec3& point_1 = data->point.xyz[index_1];
      const vec3& point_2 = data->point.xyz[index_2];
      const vec3& point_3 = data->point.xyz[index_3];

      float distance_1_2 = glm::distance(point_1, point_2);
      float distance_1_3 = glm::distance(point_1, point_3);
      float distance_2_3 = glm::distance(point_2, point_3);

      if(point_1 != empty && point_2 != empty && point_3 != empty &&
        distance_1_2 <= threshold && distance_1_3 <= threshold && distance_2_3 <= threshold){
        // Compute triangle normal
        glm::vec3 normal = glm::normalize(glm::cross(point_2 - point_1, point_3 - point_1));
        Nxyz[index_1] = normal;
        Nxyz[index_2] = normal;
        Nxyz[index_3] = normal;
      }
    }

    if(toggle) i += 1;
    toggle = !toggle;
  }

  data->point.Nxyz = Nxyz;

  //---------------------------
}
void Normal::compute_normal_with_neighbors(utl::type::Data* data, int ktruc) {
  if(data->point.xyz.size() == 0) return;
  if(data->width == -1 || data->height == -1) return;
  //---------------------------

  //Prepare data
  vector<vec3> Nxyz(data->point.xyz.size(), vec3(0.0f));
  vec3 empty = vec3(0, 0, 0);
  float threshold = 0.1f;
  int knn = 2;

  //Loop
  #pragma omp parallel for collapse(2) schedule(static)
  for(int i=0; i<data->height; i++){
    for(int j=0; j<data->width; j++){
      // Calculate the indices of the neighbor points
      vector<vec3> vec_nn;
      vector<int> vec_idx;
      vec3& point = data->point.xyz[i * data->width + j];
      if(point == empty || Nxyz[i * data->width + j] != empty) continue;

      this->compute_knn(point, vec_nn, vec_idx, knn, data, i, j, threshold);
      glm::mat3 covariance = compute_covariance(vec_nn);
      glm::vec3 normal = compute_normal_from_covariance(covariance);
      this->compute_normal_orientation(normal, point);

      Nxyz[i * data->width + j] = normal;
      for(int m=0; m<vec_idx.size(); m++){
        Nxyz[vec_idx[m]] = normal;
      }
    }
  }

  data->point.Nxyz = Nxyz;

  //---------------------------
}

//Subfunction
void Normal::compute_knn(vec3& point, vector<vec3>& vec_nn, vector<int>& vec_idx, int knn, utl::type::Data* data, int i, int j, float threshold){
  //---------------------------

  for(int k=-knn; k<=knn; k++){
    int i_neighbor = (i + k) * data->width;
    if(i_neighbor < 0) continue;

    for(int l=-knn; l<=knn; l++){
      int j_neighbor = j + l;
      if(j_neighbor < 0) continue;

      vec3& nn = data->point.xyz[i_neighbor + j_neighbor];

      if(nn != vec3(0, 0, 0)){
        float dist = glm::distance(point, nn);
        if(dist < threshold){
          vec_nn.push_back(nn);
          vec_idx.push_back(i_neighbor + j_neighbor);
        }
      }

    }
  }

  //---------------------------
}
glm::mat3 Normal::compute_covariance(const std::vector<glm::vec3>& points){
  //---------------------------

  glm::vec3 centroid(0.0f);
  for (const auto& point : points) {
      centroid += point;
  }
  centroid /= static_cast<float>(points.size());

  glm::mat3 covariance(0.0f);
  for (const auto& point : points) {
      glm::vec3 deviation = point - centroid;
      covariance += glm::outerProduct(deviation, deviation);
  }
  covariance /= static_cast<float>(points.size());

  //---------------------------
  return covariance;
}
glm::vec3 Normal::compute_normal_from_covariance(const glm::mat3& covariance){
  //---------------------------

  // Convert glm::mat3 to Eigen::Matrix3f
  Eigen::Matrix3f eigenCovariance;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
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
void Normal::compute_normal_orientation(glm::vec3& normal, const glm::vec3& point){
  //---------------------------

  // Check orientation towards the origin
  glm::vec3 centroid(0.0f); // Assuming the origin is (0, 0, 0)
  float dotProduct = glm::dot(normal, centroid - point);
  if (dotProduct < 0.0f) {
    // Invert the normal
    normal = -normal;
  }

  //---------------------------
}



}
