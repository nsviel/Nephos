#include "Exporter.h"

#include <Loader/Namespace.h>


namespace ldr{

//Constructor / Destructor
Exporter::Exporter(ldr::Node* node_loader){
  //---------------------------

  this->ldr_format = node_loader->get_ldr_format();

  //---------------------------
}
Exporter::~Exporter(){}

//Main functions
void Exporter::export_data(utl::base::Data* data){
  //---------------------------



  //---------------------------
}

}
