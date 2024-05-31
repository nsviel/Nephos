#include "Glyph.h"

#include <Data/Namespace.h>


namespace dat{

//Constructor / Destructor
Glyph::Glyph(dat::Node* node_data){
  //---------------------------

  this->node_data = node_data;
  this->dat_entity = node_data->get_dat_entity();
  this->dat_entity = node_data->get_dat_entity();

  //---------------------------
}
Glyph::~Glyph(){}

//Main function
void Glyph::insert_glyph(dat::base::Set* set, dat::base::Glyph* glyph){
  dat::Entity* dat_entity = node_data->get_dat_entity();
  //---------------------------

  glyph->create();
  dat_entity->init_entity(glyph);
  dat_set->insert_entity(set, glyph);

  //---------------------------
}
void Glyph::insert_glyph(dat::base::Entity* entity, dat::base::Glyph* glyph){
  //---------------------------

  glyph->create();
  dat_entity->init_entity(glyph);
  entity->list_glyph.push_back(glyph);

  //---------------------------
}
void Glyph::update_glyph(dat::base::Entity* entity){
  //----------------------------

  //Update own glyph data
  for(int i=0; i<entity->list_glyph.size(); i++){
    dat::base::Glyph* glyph = *next(entity->list_glyph.begin(), i);
    glyph->update_glyph(entity);
    dat_entity->update_data(glyph);

    //Reccursivity
    this->update_glyph(glyph);
  }

  //----------------------------
}
void Glyph::create_glyph(dat::base::Entity* entity){
  //----------------------------

  //Update own glyph data
  for(int i=0; i<entity->list_glyph.size(); i++){
    dat::base::Glyph* glyph = *next(entity->list_glyph.begin(), i);

    glyph->create();
    dat_entity->init_entity(glyph);
  }

  //----------------------------
}

}
