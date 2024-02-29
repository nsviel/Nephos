#include "Set.h"


namespace utl::type{

Set::Set(){
  //---------------------------


  //---------------------------
}
Set::Set(std::string name){
  //---------------------------

  this->name = name;

  //---------------------------
}

//Subset function
utl::type::Set* Set::get_subset(std::string name){
  //---------------------------

  for(int i=0; i<list_subset.size(); i++){
    utl::type::Set* subset = *next(list_subset.begin(),i);
    if(subset->name == name){
      return subset;
    }
  }

  std::cout<<"[error] Set not found ["<<name<<"]"<<std::endl;

  //---------------------------
  return nullptr;
}


//Subfunction
void Set::set_visibility(bool value){
  //---------------------------

  for(int i=0; i<list_entity.size(); i++){
    utl::type::Entity* entity = *next(list_entity.begin(), i);
    entity->set_visibility(value);
  }

  //---------------------------
}




}
