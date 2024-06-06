#include "Snapshot.h"

#include <Loader/Namespace.h>


namespace ldr::io{

//Constructor / Destructor
Snapshot::Snapshot(ldr::Node* node_loader){
  //---------------------------

  this->insert_recorder(new format::ply::Recorder());

  //---------------------------
}
Snapshot::~Snapshot(){}

//Main functions
void Snapshot::insert_recorder(ldr::base::Recorder* recorder){
  //---------------------------

  this->vec_recorder.push_back(recorder);

  //---------------------------
}

}
