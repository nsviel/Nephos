#pragma once

#include <Data/Base/Sensor/Sensor.h>
#include <Utility/Base/Data/Data.h>
#include <string>

namespace dat::base{class Sensor;}


namespace dat::base{

struct Recorder{
  //---------------------------

  virtual bool record_sensor(std::shared_ptr<dat::base::Sensor> sensor, std::string path){return false;}

  std::string format = "";
  float size = 0;
  float ts_beg = 0;
  float ts_rec = 0;

  //---------------------------
};

}
