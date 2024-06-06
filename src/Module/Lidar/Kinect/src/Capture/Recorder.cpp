#include "Recorder.h"

#include <Kinect/Namespace.h>
#include <Profiler/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n::capture{

//Constructor / Destructor
Recorder::Recorder(){
  //---------------------------

  this->format = "mkv";

  //---------------------------
}
Recorder::~Recorder(){}

//Main function
void Recorder::record_sensor(dyn::base::Sensor* sensor, std::string path){
  //---------------------------

  if(k4n::structure::Sensor* k4n_sensor = dynamic_cast<k4n::structure::Sensor*>(sensor)){
    if(!k4n_sensor->device.handle.is_valid() || path == "") return;

    this->export_start(k4n_sensor, path);
    this->export_loop(k4n_sensor, path);
    this->export_stop(k4n_sensor);
  }

  //---------------------------
}

//Subfunction
void Recorder::export_start(k4n::structure::Sensor* sensor, std::string path){
  //---------------------------

  //Recorder
  k4a::record& recorder = sensor->device.recorder;
  if(!sensor->state.record || recorder.is_valid()) return;

  //Check if directory exists, if not create it
  std::string path_dir = utl::path::get_dir_from_path(path);
  if(!utl::directory::is_exist(path_dir)){
    utl::directory::create(path_dir);
  }

  //Create recorder and file, and write header
  recorder = k4a::record::create(path.c_str(), sensor->device.handle, sensor->device.configuration);
  recorder.write_header();

  //Set info
  this->size = 0;
  this->ts_beg = sensor->timestamp.current;

  //---------------------------
}
void Recorder::export_loop(k4n::structure::Sensor* sensor, std::string path){
  //---------------------------

  //Recorder
  k4a::record& recorder = sensor->device.recorder;
  if(!sensor->state.record || !recorder.is_valid()) return;

  //Record capture
  k4a::capture* capture = sensor->device.capture;
  recorder.write_capture(*capture);

  //Set info
  this->size = utl::file::size(path);
  sensor->timestamp.record = sensor->timestamp.current - ts_beg;

  //---------------------------
}
void Recorder::export_stop(k4n::structure::Sensor* sensor){
  //---------------------------

  //Recorder
  k4a::record& recorder = sensor->device.recorder;
  if(sensor->state.record || !recorder.is_valid()) return;

  //Flush to file
  recorder.flush();
  recorder.close();

  //---------------------------
}

}
