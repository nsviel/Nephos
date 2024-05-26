#include "Recorder.h"

#include <Utility/Namespace.h>
#include <Loader/Namespace.h>


namespace format::ply{

//Constructor / Destructor
Recorder::Recorder(){
  //---------------------------

  this->ply_exporter = new format::ply::Exporter();


  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::record_bin_ply(utl::base::Data* data, utl::base::Pose* pose, std::string path){
  //---------------------------

  std::ofstream file(path, std::ios::binary | std::ios::app);

  if(utl::file::is_empty(path)){
    std::string format = "binary_little_endian";
    ply_exporter->write_header(file, format, data);
  }

  ply_exporter->write_data_binary(file, data, pose);

  file.close();

  //---------------------------
}

}
