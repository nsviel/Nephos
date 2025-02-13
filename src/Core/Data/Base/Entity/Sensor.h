#pragma once

#include <Data/Base/Entity/Object.h>
#include <Data/Sensor/Structure/Timestamp.h>
#include <Data/Sensor/Thread/Thread.h>
#include <Data/Sensor/Structure/Info.h>
#include <Data/Sensor/Structure/State.h>
#include <Data/Sensor/Graph/Graph.h>
#include <Data/Sensor/Structure/Calibration.h>
#include <Profiler/Monitor/src/Component/Profiler.h>
#include <string>


namespace dat::base{

struct Sensor : public dat::base::Object, public dat::sensor::Thread{
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
  virtual void gui_info(){}
  virtual void gui_config(){}

  dat::sensor::Info info;
  dat::sensor::Timestamp timestamp;
  dat::sensor::State state;
  dat::sensor::Graph graph;
  dat::sensor::Calibration calibration;
  prf::monitor::Profiler profiler;
  std::string type_sensor = "";

  //---------------------------
};

}
