#include "Exporter.h"

#include <Graph/Namespace.h>
#include <Scene/Namespace.h>


namespace scene{

//Constructor / Destructor
Exporter::Exporter(scene::Node* node_scene){
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
