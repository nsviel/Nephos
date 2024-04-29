#include "Exporter.h"

#include <Loader/Namespace.h>
#include <Scene/Namespace.h>


namespace ldr{

//Constructor / Destructor
Exporter::Exporter(ldr::Node* node_scene){
  //---------------------------

  this->ldr_format = node_scene->get_scene_format();

  //---------------------------
}
Exporter::~Exporter(){}

//Main functions
void Exporter::export_data(utl::type::Data* data){
  //---------------------------



  //---------------------------
}

}
