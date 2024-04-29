#include "Exporter.h"

#include <Scene/Namespace.h>
#include <Scene/Namespace.h>


namespace ldr{

//Constructor / Destructor
Exporter::Exporter(sce::Node* node_scene){
  //---------------------------

  this->sce_format = node_scene->get_scene_format();

  //---------------------------
}
Exporter::~Exporter(){}

//Main functions
void Exporter::export_data(utl::type::Data* data){
  //---------------------------



  //---------------------------
}

}
