#include "KNN.h"

#include <Utility/Namespace.h>
#include <flann/flann.hpp>
#include <cstdlib>
#include <chrono>


namespace dat::atr::normal{

// Constructor / Destructor
KNN::KNN(){
  //---------------------------

  this->time = 0;
  this->R_thres = 0.1f;

  //---------------------------
}
KNN::~KNN(){}

//Main function
void KNN::compute_normal(utl::base::Data& data, int k){
  if(data.xyz.size() == 0) return;
  //---------------------------

   auto start = std::chrono::high_resolution_clock::now();

  //Prepare data
  this->k = k;
  data.Nxyz = std::vector<glm::vec3>(data.xyz.size(), glm::vec3(0.0f));
  glm::vec3 centroid = math::centroid(data.xyz);

  // Convert point cloud to FLANN matrix
  flann::Matrix<float> dataset(new float[data.xyz.size() * 3], data.xyz.size(), 3);
  for(size_t i = 0; i < data.xyz.size(); ++i){
      dataset[i][0] = data.xyz[i].x;
      dataset[i][1] = data.xyz[i].y;
      dataset[i][2] = data.xyz[i].z;
  }

  // Build the FLANN index
  flann::Index<flann::L2<float>> index(dataset, flann::KDTreeIndexParams(4));
  index.buildIndex();

  // Loop
  #pragma omp parallel for
  for(size_t i = 0; i < data.xyz.size(); ++i){
    glm::vec3& point = data.xyz[i];
    if(point == glm::vec3(0, 0, 0) || data.Nxyz[i] != glm::vec3(0, 0, 0)) continue;

    // Find k nearest neighbors
    std::vector<std::vector<size_t>> indices(1);
    std::vector<std::vector<float>> dists(1);
    flann::Matrix<float> query(new float[3], 1, 3);
    query[0][0] = point.x;
    query[0][1] = point.y;
    query[0][2] = point.z;

    index.knnSearch(query, indices, dists, k, flann::SearchParams(128));

    std::vector<glm::vec3> vec_nn;
    for(size_t j = 0; j < indices[0].size(); ++j){
      vec_nn.push_back(data.xyz[indices[0][j]]);
    }

    delete[] query.ptr();

    // Compute normal
    glm::mat3 covariance = math::compute_covariance(vec_nn);
    glm::vec3 normal = math::compute_normal_from_covariance(covariance);

    // Adjust normal orientation
    glm::vec3 to_centroid = centroid - point;
    if(glm::dot(normal, to_centroid) < 0){
      normal = -normal;
    }

    // Store same result for each nn
    for(size_t j = 0; j < indices[0].size(); ++j){
      data.Nxyz[indices[0][j]] = normal;
    }
  }

  delete[] dataset.ptr();

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;
  this->time = duration.count();

  //---------------------------
}

//Subfunction
void KNN::compute_knn(std::vector<glm::vec3>& vec_nn, std::vector<int>& vec_idx, glm::vec3& point, utl::base::Data& data, int i, int j){
  //---------------------------

  for(int v=-k; v<=k; v++){
    int i_nn = (i + v) * data.width;
    if(i_nn < 0) continue;

    for(int h=-k; h<=k; h++){
      int j_nn = j + h;
      if(j_nn < 0) continue;

      //Get neighbor
      int idx = i_nn + j_nn;
      glm::vec3& nn = data.xyz[idx];
      if(nn == glm::vec3(0, 0, 0)) continue;

      //Check distance with interest point
      float dist = glm::distance(point, nn);
      if(dist > R_thres) continue;

      //Else store it
      vec_nn.push_back(nn);
      vec_idx.push_back(idx);
    }
  }

  //---------------------------
}

}
