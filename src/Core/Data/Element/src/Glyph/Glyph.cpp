#include "Glyph.h"

#include <Data/Element/Namespace.h>
#include <Data/Base/Namespace.h>


namespace dat::elm{

//Constructor / Destructor
Glyph::Glyph(dat::elm::Node* node_element){
  //---------------------------

  this->dat_set = node_element->get_dat_set();
  this->dat_entity = node_element->get_dat_entity();

  //---------------------------
}
Glyph::~Glyph(){}

//Main function
void Glyph::insert_glyph(std::shared_ptr<dat::base::Set> set, std::shared_ptr<dat::base::Glyph> glyph){
  //---------------------------

  this->create_glyph(glyph);
  dat_set->insert_entity(set, glyph);

  //---------------------------
}
void Glyph::insert_glyph(std::shared_ptr<dat::base::Entity> entity, std::shared_ptr<dat::base::Glyph> glyph){
  //---------------------------

  this->create_glyph(glyph);
  entity->list_glyph.push_back(glyph);

  //---------------------------
}
void Glyph::insert_glyph(std::shared_ptr<dat::base::Entity> entity){
  //----------------------------

  //Update own glyph data
  for(auto& glyph : entity->list_glyph){
    this->create_glyph(glyph);
  }

  //----------------------------
}

//Update function
void Glyph::update_glyph(std::shared_ptr<dat::base::Entity> entity){
  //----------------------------

  //Update own glyph data
  for(auto& glyph : entity->list_glyph){
    glyph->update_glyph(entity);
    dat_entity->update_data(glyph);

    //Reccursivity
    this->update_glyph(glyph);
  }

  //----------------------------
}
void Glyph::update_glyph(std::shared_ptr<dat::base::Object> object, int type){
  //----------------------------

  //Update own glyph data
  for(int i=0; i<object->list_glyph.size(); i++){
    std::shared_ptr<dat::base::Glyph> glyph = *next(object->list_glyph.begin(), i);
    if(glyph->type == type){
      glyph->update_glyph(object);
      dat_entity->update_data(glyph);
    }

    //Reccursivity
    this->update_glyph(glyph);
  }

  //----------------------------
}

//Subfunction
void Glyph::create_glyph(std::shared_ptr<dat::base::Glyph> glyph){
  //----------------------------

  glyph->create();
  dat_entity->init_entity(glyph);

  //Update own glyph data
  for(int i=0; i<glyph->list_glyph.size(); i++){
    dat::base::Glyph* subglyph = *next(glyph->list_glyph.begin(), i);
    this->create_glyph(subglyph);
  }

  //----------------------------
}

}
