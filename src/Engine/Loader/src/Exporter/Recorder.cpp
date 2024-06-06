#include "Recorder.h"

#include <Loader/Namespace.h>
#include <Dynamic/Namespace.h>


namespace ldr::io{

//Constructor / Destructor
Recorder::Recorder(ldr::Node* node_loader){
  //---------------------------

  this->ldr_struct = node_loader->get_ldr_struct();

  this->insert_exporter(new format::ply::Recorder());
  this->insert_exporter(new format::pts::Recorder());

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

  for(int i=0; i<vec_exporter.size(); i++){
    ldr::base::Recorder* exporter = vec_exporter[i];

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

  for(int i=0; i<vec_exporter.size(); i++){
    ldr::base::Recorder* exporter = vec_exporter[i];
    vec_format.push_back(exporter->format);
  }

  //---------------------------
  return vec_format;
}
std::vector<int> Recorder::get_supported_encoding(std::string format){
  std::vector<int> vec_encoding;
  //---------------------------

  for(int i=0; i<vec_exporter.size(); i++){
    ldr::base::Recorder* exporter = vec_exporter[i];

    if(format == exporter->format){
      vec_encoding = exporter->vec_encoding;
      break;
    }
  }

  //---------------------------
  return vec_encoding;
}
std::string Recorder::get_action_label(dat::base::Entity* entity){
  std::string label = "Save";
  //---------------------------

  if(dyn::base::Sensor* sensor = dynamic_cast<dyn::base::Sensor*>(entity)){
    label = "Record";
  }

  //---------------------------
  return label;
}

}
