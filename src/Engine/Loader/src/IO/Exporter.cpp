#include "Exporter.h"

#include <Loader/Namespace.h>


namespace ldr{

//Constructor / Destructor
Exporter::Exporter(ldr::Node* node_loader){
  //---------------------------

  this->insert_exporter(new format::ply::Exporter());

  //---------------------------
}
Exporter::~Exporter(){}

//Main functions
void Exporter::export_data(utl::base::Data* data){
  //---------------------------



  //---------------------------
}
void Exporter::insert_exporter(ldr::base::Exporter* exporter){
  //---------------------------

  this->vec_exporter.push_back(exporter);

  //---------------------------
}

}
