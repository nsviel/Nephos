#include "Attribut.h"

#include <Utility/Namespace.h>


namespace utl::base{

//Constructor / Destructor
Attribut::Attribut(){
  //---------------------------


  //---------------------------
}
Attribut::~Attribut(){}

//Subfunction
void Attribut::set_attribut_data(utl::base::Data* data, std::string name, std::vector<float>& vec){
  //---------------------------

  this->create_attribut(data, name);
  utl::base::data::Attribut* attribut = get_attribut(data, name);

  if(attribut){
    attribut->data = vec;
  }

  //---------------------------
}
std::vector<float>& Attribut::get_attribut_data(utl::base::Data* data, std::string name){
  //---------------------------

  this->create_attribut(data, name);
  utl::base::data::Attribut* attribut = get_attribut(data, name);

  // Check if attribut is nullptr
  if(!attribut){
    static std::vector<float> empty_vector;
    return empty_vector;
  }

  //---------------------------
  return attribut->data;
}
void Attribut::create_attribut(utl::base::Data* data, std::string name){
  //---------------------------

  //Check if attribut is already present
  for(int i=0; i<data->vec_attribut.size(); i++){
    utl::base::data::Attribut& attribut = data->vec_attribut[i];
    if(attribut.name == name) return;
  }

  //Create it
  utl::base::data::Attribut attribut;
  attribut.name = name;
  data->vec_attribut.push_back(attribut);

  //---------------------------
}
utl::base::data::Attribut* Attribut::get_attribut(utl::base::Data* data, std::string name){
  //---------------------------

  //Check if attribut is already present
  for(int i=0; i<data->vec_attribut.size(); i++){
    utl::base::data::Attribut& attribut = data->vec_attribut[i];
    if(attribut.name == name) return &attribut;
  }

  //---------------------------
  return nullptr;
}


}
