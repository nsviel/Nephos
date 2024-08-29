#pragma once

#include <Data/Base/Entity/Object.h>
#include <Data/Base/Sensor/Timestamp.h>
#include <Data/Base/Sensor/Calibration.h>
#include <Data/Base/Sensor/Thread.h>
#include <Data/Base/Sensor/Info.h>
#include <Data/Base/Sensor/State.h>
#include <Profiler/Monitor/src/Component/Profiler.h>


namespace dat::base{

struct Sensor : public dat::base::Object, public dat::base::sensor::Thread{
  //---------------------------

  void start(){this->start_thread();}
  void stop(){this->stop_thread();}
  void pause(bool value){this->pause_thread(value);}
  void restart(){this->stop(); this->start();}

  virtual void query(float value){}

  dat::base::sensor::Info info;
  dat::base::sensor::Timestamp timestamp;
  dat::base::sensor::Calibration calibration;
  dat::base::sensor::State state;
  prf::monitor::Profiler profiler;

  //---------------------------
};

}
