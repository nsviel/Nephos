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
std::vector<float>& Attribut::get_attribut_data(utl::base::Data* data, std::string name){
  //---------------------------

  for(int i=0; i<data->vec_attribut.size(); i++){
    utl::base::data::Attribut& attribut = data->vec_attribut[i];
    if(attribut.name == name) return attribut.data;
  }

  std::cout<<"[error] attribut name doesn't exists"<<std::endl;
  static std::vector<float> empty_vector;

  //---------------------------
  return empty_vector;
}
utl::base::data::Attribut* Attribut::get_attribut(utl::base::Data* data, std::string name){
  //---------------------------

  for(int i=0; i<data->vec_attribut.size(); i++){
    utl::base::data::Attribut& attribut = data->vec_attribut[i];
    if(attribut.name == name) return &attribut;
  }

  std::cout<<"[error] attribut name doesn't exists"<<std::endl;

  //---------------------------
  return nullptr;
}

}
