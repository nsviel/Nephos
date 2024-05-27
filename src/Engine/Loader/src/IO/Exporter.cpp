#include "Exporter.h"

#include <Loader/Namespace.h>


namespace ldr::io{

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

//Exporter function
void Exporter::insert_exporter(ldr::base::Exporter* exporter){
  //---------------------------

  this->vec_exporter.push_back(exporter);

  //---------------------------
}
std::vector<std::string> Exporter::get_supported_format(){
  std::vector<std::string> vec_format;
  //---------------------------

  for(int i=0; i<vec_exporter.size(); i++){
    ldr::base::Exporter* exporter = vec_exporter[i];
    vec_format.push_back(exporter->format);
  }

  //---------------------------
  return vec_format;
}

}
