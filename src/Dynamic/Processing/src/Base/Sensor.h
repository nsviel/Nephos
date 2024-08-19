#pragma once

#include <Utility/Namespace.h>
#include <Element/src/Base/Object.h>
#include <Profiler/src/Dynamic/Profiler.h>
#include <Processing/src/Base/Timestamp.h>
#include <Processing/src/Base/Calibration.h>
#include <Processing/src/Base/State.h>
#include <Processing/src/Base/Recorder.h>

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
