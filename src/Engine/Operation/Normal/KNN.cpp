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
  this->k = 5;

  //---------------------------
}
KNN::~KNN(){}

//Main function
void KNN::compute_normal_from_grid(utl::base::Data* data){
  if(data->xyz.size() == 0) return;
  if(data->width == -1 || data->height == -1) return;
  //---------------------------

  //Prepare data
  std::vector<glm::vec3> Nxyz(data->xyz.size(), glm::vec3(0.0f));

  //Loop
  #pragma omp parallel for collapse(2) schedule(static)
  for(int i=0; i<data->height; i++){
    for(int j=0; j<data->width; j++){
      //Get point and check
      int idx = i * data->width + j;
      glm::vec3& point = data->xyz[idx];
      if(point == glm::vec3(0, 0, 0) || Nxyz[idx] != glm::vec3(0, 0, 0)) continue;

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
        Nxyz[vec_idx[m]] = normal;
      }
    }
  }

  data->Nxyz = Nxyz;

  //---------------------------
}

//Subfunction
void KNN::compute_knn(std::vector<glm::vec3>& vec_nn, std::vector<int>& vec_idx, glm::vec3& point, utl::base::Data* data, int i, int j){
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
void KNN::set_visibility(dat::base::Object* object, bool value){
  //---------------------------

  dat::base::Glyph* normal = object->get_glyph(dat::object::glyph::NORMAL);
  normal->set_visibility(value);

  //---------------------------
}

}
