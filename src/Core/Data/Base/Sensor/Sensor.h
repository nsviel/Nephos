#pragma once

#include <Data/Base/Entity/Object.h>
#include <Data/Base/Sensor/Timestamp.h>
#include <Data/Base/Sensor/Calibration.h>
#include <Data/Base/Sensor/State.h>
#include <Data/Base/Sensor/Info.h>
#include <Profiler/Monitor/src/Component/Profiler.h>
#include <Utility/Namespace.h>


namespace dat::base{

struct Sensor : public dat::base::Object, public sys::thread::Worker, public std::enable_shared_from_this<Sensor>{
  //---------------------------

  void restart(){
    this->stop();
    this->start();
  }

  virtual void start(){}
  virtual void stop(){}
  virtual void query(float value){}

  dat::base::Info info;
  dat::base::Timestamp timestamp;
  dat::base::State state;
  dat::base::Calibration calibration;
  prf::monitor::Profiler profiler;

  //---------------------------
};

}
