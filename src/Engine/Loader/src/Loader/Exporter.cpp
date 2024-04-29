#include "Exporter.h"

#include <Loader/Namespace.h>
#include <Scene/Namespace.h>


namespace ldr{

//Constructor / Destructor
Exporter::Exporter(ldr::Node* node_loader){
  //---------------------------

  this->ldr_format = node_loader->get_scene_format();

  //---------------------------
}
Exporter::~Exporter(){}

//Main functions
void Exporter::export_data(utl::type::Data* data){
  //---------------------------



  //---------------------------
}

}
