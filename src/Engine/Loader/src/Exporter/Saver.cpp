#include "Saver.h"

#include <Loader/Namespace.h>


namespace ldr::io{

//Constructor / Destructor
Saver::Saver(ldr::Node* node_loader){
  //---------------------------

  this->insert_recorder(new format::ply::Recorder());

  //---------------------------
}
Saver::~Saver(){}

//Main functions
void Saver::insert_recorder(ldr::base::Recorder* recorder){
  //---------------------------

  this->vec_recorder.push_back(recorder);

  //---------------------------
}

}
