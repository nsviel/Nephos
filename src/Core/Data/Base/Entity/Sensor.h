#pragma once

#include <Data/Base/Entity/Object.h>
#include <Data/Sensor/Structure/Timestamp.h>
#include <Data/Sensor/Structure/Calibration.h>
#include <Data/Sensor/Structure/Thread.h>
#include <Data/Sensor/Structure/Info.h>
#include <Data/Sensor/Structure/State.h>
#include <Profiler/Monitor/src/Component/Profiler.h>


namespace dat::base{

struct Sensor : public dat::base::Object, public dat::base::sensor::Thread{
  //---------------------------

  Sensor(){
    this->type_entity = "sensor";
  }

  void start(){this->start_thread();}
  void stop(){this->stop_thread();}
  void pause(bool value){this->pause_thread(value);}
  void restart(){this->stop(); this->start();}
  void clean(){this->stop_thread();}

  virtual void query(float value){}

  dat::base::sensor::Info info;
  dat::base::sensor::Timestamp timestamp;
  dat::base::sensor::Calibration calibration;
  dat::base::sensor::State state;
  prf::monitor::Profiler profiler;

  //---------------------------
};

}
