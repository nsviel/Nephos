#pragma once

#include <Data/Base/Entity/Object.h>
#include <Data/Base/Sensor/Timestamp.h>
#include <Data/Base/Sensor/Calibration.h>
#include <Data/Base/Sensor/State.h>
#include <Data/Base/Sensor/Recorder.h>
#include <Profiler/Monitor/src/Component/Profiler.h>
#include <Utility/Namespace.h>


namespace dat::base{class Recorder;}


namespace dat::base{

struct Sensor : public dat::base::Object, public sys::thread::Worker, public std::enable_shared_from_this<Sensor>{
  //---------------------------

  void clean(){
    //---------------------------

    this->stop_thread();

    //---------------------------
  }

  virtual void manage_query(float ts_querry){}
  virtual void manage_configuration(){}
  virtual void manage_reset(){}
  virtual void gui_config(){}

  dat::base::Timestamp timestamp;
  dat::base::State state;
  dat::base::Calibration calibration;
  prf::monitor::Profiler profiler;

  std::string device_name = "";
  std::string serial_number = "";
  std::string depth_mode = "";
  std::vector<uint16_t> buffer_depth;
  std::vector<uint16_t> buffer_ir;
  std::vector<dat::base::Recorder*> vec_recorder;
  std::vector<std::string> vec_depth_mode;

  //---------------------------
};

}
