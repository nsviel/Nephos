#include "Capture.h"

#include <IO/Importer/Namespace.h>
#include <IO/Format/Namespace.h>
#include <Data/Namespace.h>
#include <Utility/Namespace.h>


namespace io::imp{

//Constructor / Destructor
Capture::Capture(io::imp::Node* node_importer){
  //---------------------------

  this->io_struct = node_importer->get_io_struct();
  this->io_operation = node_importer->get_io_operation();

  //---------------------------
}
Capture::~Capture(){}

//Main function

}
