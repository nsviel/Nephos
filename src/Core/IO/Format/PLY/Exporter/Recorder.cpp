#include "Recorder.h"
#include "Exporter.h"

#include <Utility/Namespace.h>


namespace fmt::ply{

//Constructor / Destructor
Recorder::Recorder(){
  //---------------------------

  this->ply_exporter = new fmt::ply::Exporter();
  this->format = ".ply";

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::record_binary(utl::base::Data& data, glm::mat4 mat, std::string path){
  //---------------------------
/*
  std::ofstream file(path, std::ios::binary | std::ios::app);

  if(utl::file::is_empty(path)){
    std::string format = "binary_little_endian";
    ply_exporter->write_header(file, format, data);
  }

  //ply_exporter->write_data_binary(file, data, mat);

  file.close();
*/
  //---------------------------
}

}
