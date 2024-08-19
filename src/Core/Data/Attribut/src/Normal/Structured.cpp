#include "Structured.h"

#include <Data/Attribut/Namespace.h>
#include <Data/Element/Namespace.h>
#include <Data/Image/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <cstdlib>
#include <chrono>


namespace dat::atr::normal{

// Constructor / Destructor
Structured::Structured(){
  //---------------------------

  this->ope_converter = new dat::img::Converter();

  this->time = 0;
  this->R_thres = 0.1f;

  //---------------------------
}
Structured::~Structured(){}

//Main function
void Structured::compute_normal(utl::base::Data* data){
  if(data->xyz.size() == 0) return;
  if(data->width == -1 || data->height == -1) return;
  //---------------------------

  //Prepare data
  auto start = std::chrono::high_resolution_clock::now();
  data->Nxyz = std::vector<glm::vec3>(data->xyz.size(), glm::vec3(0.0f));

  //Loop
  #pragma omp parallel for collapse(2) schedule(static)
  for(int i=0; i<data->height; i++){
    for(int j=0; j<data->width; j++){
      //Get point and check
      int idx = i * data->width + j;
      glm::vec3& point = data->xyz[idx];
      if(point == glm::vec3(0, 0, 0) || data->Nxyz[idx] != glm::vec3(0, 0, 0)) continue;

      //Find neighbor point indices
      std::vector<glm::vec3> vec_nn;
      std::vector<int> vec_idx;
      this->compute_knn(vec_nn, vec_idx, point, data, i, j);

      //Compute normal
      glm::mat3 covariance = math::compute_covariance(vec_nn);
      glm::vec3 normal = math::compute_normal_from_covariance(covariance);
      math::compute_normal_orientation(normal, point);

      //Store same result for each nn
      for(int m=0; m<vec_idx.size(); m++){
        data->Nxyz[vec_idx[m]] = normal;
      }
    }
  }

  //Algorithm duration
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = end - start;
  this->time = duration.count();

  //---------------------------
}

//Subfunction
void Structured::compute_knn(std::vector<glm::vec3>& vec_nn, std::vector<int>& vec_idx, glm::vec3& point, utl::base::Data* data, int i, int j){
  //---------------------------

  for(int v=-k; v<=k; v++){
    int i_nn = (i + v) * data->width;
    if(i_nn < 0) continue;

    for(int h=-k; h<=k; h++){
      int j_nn = j + h;
      if(j_nn < 0) continue;

      //Get neighbor
      int idx = i_nn + j_nn;
      glm::vec3& nn = data->xyz[idx];
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
