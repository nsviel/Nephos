#pragma once

#include <Data/Base/Entity/Object.h>
#include <Data/Base/Sensor/Timestamp.h>
#include <Data/Base/Sensor/Calibration.h>
#include <Data/Base/Sensor/State.h>
#include <Data/Base/Sensor/Info.h>
#include <Profiler/Monitor/src/Component/Profiler.h>


namespace dat::base{

struct Sensor : public dat::base::Object{
  //---------------------------

  void restart(){
    this->stop();
    this->start();
  }

  virtual void start(){}
  virtual void stop(){}
  virtual void pause(bool value){this->state.pause = value;}
  virtual void query(float value){}

  dat::base::sensor::Info info;
  dat::base::sensor::Timestamp timestamp;
  dat::base::sensor::State state;
  dat::base::sensor::Calibration calibration;
  prf::monitor::Profiler profiler;

  //---------------------------
};

}
