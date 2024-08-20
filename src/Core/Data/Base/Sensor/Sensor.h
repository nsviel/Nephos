#pragma once

#include <Data/Base/Entity/Object.h>
#include <Data/Base/Sensor/Timestamp.h>
#include <Data/Base/Sensor/Calibration.h>
#include <Data/Base/Sensor/State.h>
#include <Data/Base/Sensor/Recorder.h>
#include <Profiler/src/Dynamic/Profiler.h>
#include <Utility/Namespace.h>


namespace dyn::prc::base{class Recorder;}


namespace dyn::prc::base{

struct Sensor : public dat::base::Object, public sys::thread::Worker{
  //---------------------------

  void clean(){
    //---------------------------

    this->stop_thread();

    //---------------------------
  }

  virtual glm::vec3 convert_depth_2d_to_3d(glm::ivec2 point){return glm::vec3(0);}
  virtual void manage_query(float ts_querry){}
  virtual void manage_configuration(){}
  virtual void manage_reset(){}
  virtual void gui_config(){}

  dyn::prc::base::Timestamp timestamp;
  dyn::prc::base::State state;
  dyn::prc::base::Calibration calibration;
  prf::dynamic::Profiler profiler;

  std::string device_name = "";
  std::string serial_number = "";
  std::string depth_mode = "";
  std::vector<uint16_t> buffer_depth;
  std::vector<uint16_t> buffer_ir;
  std::vector<dyn::prc::base::Recorder*> vec_recorder;
  std::vector<std::string> vec_depth_mode;

  //---------------------------
};

}