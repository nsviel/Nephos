#include "Recorder.h"

#include <Loader/Namespace.h>


namespace ldr::io{

//Constructor / Destructor
Recorder::Recorder(ldr::Node* node_loader){
  //---------------------------

  this->insert_recorder(new format::ply::Recorder());

  //---------------------------
}
Recorder::~Recorder(){}

//Main functions
void Recorder::insert_recorder(ldr::base::Recorder* recorder){
  //---------------------------

  this->vec_recorder.push_back(recorder);

  //---------------------------
}

}
