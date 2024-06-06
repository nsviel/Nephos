#pragma once

#include <Dynamic/src/Base/Sensor.h>
#include <Utility/Base/Type/Data.h>
#include <string>

namespace dyn::base{class Sensor;}


namespace dyn::base{

struct Recorder{
  //---------------------------

  virtual void record_sensor(dyn::base::Sensor* sensor, std::string path){}

  std::string format = "";
  float size = 0;
  float ts_beg = 0;
  float ts_rec = 0;

  //---------------------------
};

}
