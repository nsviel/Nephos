#include "Capture.h"

#include <IO/Importer/Namespace.h>
#include <IO/Format/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace io::imp{

//Constructor / Destructor
Capture::Capture(io::imp::Node* node_importer){
  //---------------------------

  this->io_importer = node_importer->get_io_importer();
  this->io_operation = node_importer->get_io_operation();

  //---------------------------
}
Capture::~Capture(){}

//Main function
void Capture::run_capture(std::string& vendor, std::string& product){
  //---------------------------

  //Get importer
  io::base::Importer* importer = io_importer->obtain_importer(vendor, product);
  if(importer == nullptr) return;

  say(importer->reference.name);

  //Get element
  std::shared_ptr<utl::base::Element> element = importer->capture();
  if(!element || element->type != "entity") return;

  //Convert into object
  auto object = std::dynamic_pointer_cast<dat::base::Object>(element);
  if(!object) return;

  //Insert it
  io_operation->insert_object(object);

  //---------------------------
}

}
