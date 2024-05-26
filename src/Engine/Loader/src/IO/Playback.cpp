#include "Playback.h"

#include <Loader/Namespace.h>


namespace ldr::io{

//Constructor / Destructor
Playback::Playback(ldr::Node* node_loader){
  //---------------------------

  this->insert_playback(new format::ply::Playback());

  //---------------------------
}
Playback::~Playback(){}

//Main functions
void Playback::insert_playback(ldr::base::Playback* playback){
  //---------------------------

  this->vec_playback.push_back(playback);

  //---------------------------
}

}
