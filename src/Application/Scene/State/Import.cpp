#include "Import.h"

#include <Core/Namespace.h>
#include <Scene/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace sce{

//Constructor / Destructor
Import::Import(sce::Node* node_scene){
  //---------------------------

  core::Node* node_core = node_scene->get_node_core();
  dat::Node* node_data = node_core->get_node_data();
  dat::gph::Node* node_graph = node_data->get_node_graph();

  this->dat_graph = node_graph->get_gph_graph();

  //---------------------------
}
Import::~Import(){}

//Main function
void Import::import_json(){
  //---------------------------


  //---------------------------
}

//Subfunction


}
