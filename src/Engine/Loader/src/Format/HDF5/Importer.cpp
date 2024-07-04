#include "Importer.h"

#include <Data/Namespace.h>
#include <Utility/Function/File/File.h>


namespace format::hdf5{

//Constructor / Destructor
Importer::Importer(){
  //---------------------------

  this->format = ".h5";

  //---------------------------
}
Importer::~Importer(){}

//Main function
utl::base::Element* Importer::import(utl::base::Path path){
  //---------------------------

  //Init
  dat::base::Object* object = new dat::base::Object();
  object->name = path.name;
  object->data.name = path.name;
  object->data.path = path;
  object->data.path.format = format;
  object->data.topology.type = utl::topology::POINT;

  //---------------------------
  return object;
}



//Subfunction


}
