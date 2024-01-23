#include "Recorder.h"

#include <Engine/Engine.h>
#include <Utility/Function/File/Info.h>


namespace k4n::src::dev{

//Constructor / Destructor
Recorder::Recorder(Engine* engine){
  //---------------------------

  this->engine = engine;
  this->default_folder = "../media/record/";

  //---------------------------
}
Recorder::~Recorder(){}

//Main function

}
