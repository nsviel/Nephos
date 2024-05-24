#include "KNN.h"

#include <Operation/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>
#include <cstdlib>


namespace ope::normal{

// Constructor / Destructor
KNN::KNN(){
  //---------------------------

  this->R_thres = 0.1f;

  //---------------------------
}
KNN::~KNN(){}

//Main function
void KNN::compute_normal_from_grid(utl::base::Data* data, int knn){
  if(data->xyz.size() == 0) return;
  if(data->width == -1 || data->height == -1) return;
  //---------------------------

  //Prepare data
  std::vector<glm::vec3> Nxyz(data->xyz.size(), glm::vec3(0.0f));

  //Loop
  #pragma omp parallel for collapse(2) schedule(static)
  for(int i=0; i<data->height; i++){
    for(int j=0; j<data->width; j++){
      // Calculate the indices of the neighbor points
      std::vector<glm::vec3> vec_nn;
      std::vector<int> vec_idx;
      glm::vec3& point = data->xyz[i * data->width + j];
      if(point == glm::vec3(0, 0, 0) || Nxyz[i * data->width + j] != glm::vec3(0, 0, 0)) continue;

      this->compute_knn(point, vec_nn, vec_idx, knn, data, i, j);
      glm::mat3 covariance = math::compute_covariance(vec_nn);
      glm::vec3 normal = math::compute_normal_from_covariance(covariance);
      math::compute_normal_orientation(normal, point);

      Nxyz[i * data->width + j] = normal;
      for(int m=0; m<vec_idx.size(); m++){
        Nxyz[vec_idx[m]] = normal;
      }
    }
  }

  data->Nxyz = Nxyz;

  //---------------------------
}

//Subfunction
void KNN::compute_knn(glm::vec3& point, std::vector<glm::vec3>& vec_nn, std::vector<int>& vec_idx, int knn, utl::base::Data* data, int i, int j){
  //---------------------------

  for(int k=-knn; k<=knn; k++){
    int i_neighbor = (i + k) * data->width;
    if(i_neighbor < 0) continue;

    for(int l=-knn; l<=knn; l++){
      int j_neighbor = j + l;
      if(j_neighbor < 0) continue;

      glm::vec3& nn = data->xyz[i_neighbor + j_neighbor];

      if(nn != glm::vec3(0, 0, 0)){
        float dist = glm::distance(point, nn);
        if(dist < R_thres){
          vec_nn.push_back(nn);
          vec_idx.push_back(i_neighbor + j_neighbor);
        }
      }

    }
  }

  //---------------------------
}
void KNN::set_visibility(dat::base::Object* object, bool value){
  //---------------------------

  dat::base::Glyph* normal = object->get_glyph(dat::object::glyph::NORMAL);
  normal->set_visibility(value);

  //---------------------------
}

}
