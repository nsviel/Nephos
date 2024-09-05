#include "Importer.h"

#include <IO/Importer/Namespace.h>
#include <IO/Format/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace io::imp{

//Constructor / Destructor
Importer::Importer(io::imp::Node* node_importer){
  //---------------------------

  this->io_struct = node_importer->get_io_struct();
  this->io_operation = node_importer->get_io_operation();

  this->insert_importer(new fmt::ply::Importer());
  this->insert_importer(new fmt::obj::Importer());
  this->insert_importer(new fmt::csv::Importer());
  this->insert_importer(new fmt::pts::Importer());
  this->insert_importer(new fmt::ptx::Importer());
  this->insert_importer(new fmt::xyz::Importer());
  this->insert_importer(new fmt::hdf5::Importer());

  //---------------------------
}
Importer::~Importer(){}

//Main function
void Importer::insert_importer(io::base::Importer* importer){
  //---------------------------

  this->vec_importer.push_back(importer);

  //---------------------------
}
io::base::Importer* Importer::obtain_importer(std::string format){
  //---------------------------

  for(int i=0; i<vec_importer.size(); i++){
    io::base::Importer* importer = vec_importer[i];

    if(importer->reference.format == format){
      return importer;
    }
  }

  //---------------------------
  return nullptr;
}

//Subfunction
bool Importer::is_format_supported(std::string format){
  if(format == "-") return false;
  //---------------------------

  for(int i=0; i<vec_importer.size(); i++){
    io::base::Importer* importer = vec_importer[i];

    if(format == importer->reference.format){
      return true;
    }
  }

  //---------------------------
  return false;
}
std::vector<std::string> Importer::get_supported_format(){
  std::vector<std::string> vec_format;
  //---------------------------

  for(int i=0; i<vec_importer.size(); i++){
    io::base::Importer* importer = vec_importer[i];
    vec_format.push_back(importer->reference.format);
  }

  //---------------------------
  return vec_format;
}

}
