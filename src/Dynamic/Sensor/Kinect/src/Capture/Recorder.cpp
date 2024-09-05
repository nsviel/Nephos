#include "Recorder.h"

#include <Kinect/Namespace.h>


namespace k4n::capture{

//Constructor / Destructor
Recorder::Recorder(){
  //---------------------------

  //this->reference.format = ".mkv";

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
bool Recorder::record_sensor(std::shared_ptr<dat::base::Sensor> sensor, std::string path){
  //---------------------------

  if(auto k4n_sensor = std::dynamic_pointer_cast<k4n::base::Sensor>(sensor)){
    if(!k4n_sensor->device.handle.is_valid() || path == "") return false;

    k4a::record& recorder = k4n_sensor->device.recorder;
    if(sensor->state.record && !recorder.is_valid()){
      this->export_start(k4n_sensor, path);
      return true;
    }
    else if(sensor->state.record && recorder.is_valid()){
      this->export_record(k4n_sensor, path);
      return true;
    }
    else if(!sensor->state.record && recorder.is_valid()){
      this->export_stop(k4n_sensor);
      return true;
    }
  }

  //---------------------------
  return false;
}

//Subfunction
void Recorder::export_start(std::shared_ptr<k4n::base::Sensor> sensor, std::string path){
  //---------------------------

  //Check if directory exists, if not create it
  std::string path_dir = utl::path::get_dir_from_path(path);
  if(!utl::directory::is_exist(path_dir)){
    utl::directory::create(path_dir);
  }

  //Create recorder and file, and write header
  k4a::record& recorder = sensor->device.recorder;
  recorder = k4a::record::create(path.c_str(), sensor->device.handle, sensor->device.configuration);
  recorder.write_header();

  //Set info
  this->size = 0;
  this->ts_beg = sensor->timestamp.current;

  //---------------------------
}
void Recorder::export_record(std::shared_ptr<k4n::base::Sensor> sensor, std::string path){
  //---------------------------
/*
  //Record capture
  k4a::capture* capture = sensor->device.capture;
  k4a::record& recorder = sensor->device.recorder;
  recorder.write_capture(*capture);

  //Set info
  this->size = utl::file::size(path);
  sensor->timestamp.record = sensor->timestamp.current - ts_beg;
*/
  //---------------------------
}
void Recorder::export_stop(std::shared_ptr<k4n::base::Sensor> sensor){
  //---------------------------

  //Flush to file
  k4a::record& recorder = sensor->device.recorder;
  recorder.flush();
  recorder.close();
  recorder = k4a::record();

  //---------------------------
}

}
