#include "Importer.h"

#include <Data/Namespace.h>
#include <Utility/Function/File/File.h>


namespace fmt::hdf5{

//Constructor / Destructor
Importer::Importer(){
  //---------------------------

  this->reference.format = ".h5";

  //---------------------------
}
Importer::~Importer(){}

//Main function
std::shared_ptr<utl::base::Element> Importer::import(utl::base::Path path){
  //---------------------------

  //Init
  std::shared_ptr<dat::base::Object> object = std::make_shared<dat::base::Object>();
  object->name = path.name;
  object->data->name = path.name;
  object->data->path = path;
  object->data->path.format = reference.format;
  object->data->topology.type = utl::topology::POINT;

  //---------------------------
  return object;
}



//Subfunction


}
