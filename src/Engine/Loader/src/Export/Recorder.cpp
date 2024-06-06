#include "Recorder.h"

#include <Loader/Namespace.h>
#include <Dynamic/Namespace.h>


namespace ldr::io{

//Constructor / Destructor
Recorder::Recorder(ldr::Node* node_loader){
  //---------------------------

  this->ldr_struct = node_loader->get_ldr_struct();

  //---------------------------
}
Recorder::~Recorder(){}

//Main functions
void Recorder::insert_recorder(ldr::base::Recorder* recorder){
  //---------------------------

  this->vec_recorder.push_back(recorder);

  //---------------------------
}

//Subfunction
bool Recorder::is_format_supported(std::string format){
  //---------------------------

  for(int i=0; i<vec_recorder.size(); i++){
    ldr::base::Recorder* exporter = vec_recorder[i];

    if(format == exporter->format){
      return true;
    }
  }

  //---------------------------
  return false;
}
std::vector<std::string> Recorder::get_supported_format(){
  std::vector<std::string> vec_format;
  //---------------------------

  for(int i=0; i<vec_recorder.size(); i++){
    ldr::base::Recorder* exporter = vec_recorder[i];
    vec_format.push_back(exporter->format);
  }

  //---------------------------
  return vec_format;
}

}
