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

  utl::base::data::Attribut* attribut = get_or_create_attribut(data, name);

  //---------------------------
  return attribut->data;;
}
utl::base::data::Attribut* Attribut::get_or_create_attribut(utl::base::Data* data, std::string name){
  //---------------------------

  //Check if attribut is already present
  for(int i=0; i<data->vec_attribut.size(); i++){
    utl::base::data::Attribut& attribut = data->vec_attribut[i];
    if(attribut.name == name) return &attribut;
  }

  //Create it
  utl::base::data::Attribut attribut;
  attribut.name = name;
  data->vec_attribut.push_back(attribut);

  //---------------------------
  return &data->vec_attribut.back();
}


}
