#include "Exporter.h"

#include <Data/Namespace.h>
#include <Utility/Function/File/File.h>


namespace fmt::hdf5{

//Constructor / Destructor
Exporter::Exporter(){
  //---------------------------

  this->format = ".h5";
  this->vec_encoding.push_back(ldr::io::ASCII);

  //---------------------------
}
Exporter::~Exporter(){}

//Main function
void Exporter::export_ascii(utl::base::Data* data, glm::mat4 mat, std::string path){
  //---------------------------

  //---------------------------
}

}
