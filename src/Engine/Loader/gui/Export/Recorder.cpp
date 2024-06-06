#include "Recorder.h"

#include <Data/Namespace.h>
#include <Loader/Namespace.h>
#include <Operation/Namespace.h>
#include <Utility/Namespace.h>
#include <Dynamic/Namespace.h>
#include <image/IconsFontAwesome6.h>


namespace ldr::gui::exporter{

//Constructor / Destructor
Recorder::Recorder(ldr::Node* node_loader){
  //---------------------------

  dat::Node* node_data = node_loader->get_node_data();

  this->ldr_struct = node_loader->get_ldr_struct();
  this->dat_selection = node_data->get_dat_selection();
  this->ldr_recorder = node_loader->get_ldr_recorder();

  //---------------------------
}
Recorder::~Recorder(){}

//Header function


}
