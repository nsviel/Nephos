#include "Attribut.h"

#include <Data/Namespace.h>


namespace ope::attribut{

// Constructor / Destructor
Attribut::Attribut(){
  //---------------------------

  this->utl_attribut = new utl::base::Attribut();

  //---------------------------
}
Attribut::~Attribut(){}

//Main function
void Attribut::compute_range(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  //---------------------------
say("---");
  std::vector<float>& R = utl_attribut->get_attribut_data(data, "R");
  std::vector<glm::vec3>& xyz = data->xyz;

  R.resize(xyz.size(), 0.0f);

  #pragma omp parallel for
  for(int i=0; i<xyz.size(); i++){
    float dist = glm::length(xyz[i]);
    R[i] = dist;
  }

  //---------------------------
}
void Attribut::compute_incidence_angle(dat::base::Entity* entity){
  utl::base::Data* data = &entity->data;
  //---------------------------

  std::vector<float>& It = utl_attribut->get_attribut_data(data, "It");
  std::vector<float>& R = utl_attribut->get_attribut_data(data, "R");
  std::vector<glm::vec3>& xyz = data->xyz;
  std::vector<glm::vec3>& Nxyz = data->Nxyz;

  It = std::vector<float>(xyz.size(), 0.0f);
  for(int i=0; i<xyz.size(); i++){
    float angle = math::compute_It(xyz[i], Nxyz[i], R[i]);
    It[i] = angle;
  }

  //---------------------------
}
void Attribut::set_unicolor(dat::base::Entity* entity){
  if(entity == nullptr) return;
  utl::base::Data* data = &entity->data;
  //---------------------------

  for(int i=0; i<data->rgb.size(); i++){
    data->rgb[i] = data->unicolor;
  }

  //---------------------------
}

}
