#include "Glyph.h"

#include <Vulkan/Namespace.h>
#include <Engine/Namespace.h>
#include <Camera/Namespace.h>
#include <Data/Namespace.h>


namespace dat{

//Constructor / Destructor
Glyph::Glyph(dat::Node* node_data){
  //---------------------------

  eng::Node* node_engine = node_data->get_node_engine();
  vk::Node* node_vulkan = node_engine->get_node_vulkan();

  this->node_data = node_data;
  this->node_engine = node_engine;
  this->dat_graph = node_data->get_dat_graph();
  this->dat_set = node_data->get_dat_set();

  //---------------------------
}
Glyph::~Glyph(){}

//Main function

void Glyph::create_glyph(dat::base::Entity* entity, dat::base::Glyph* glyph){
  dat::Entity* dat_entity = node_data->get_dat_entity();
  //---------------------------

  glyph->create();
  dat_entity->init_entity(glyph);
  entity->list_glyph.push_back(glyph);

  //---------------------------
}

}
