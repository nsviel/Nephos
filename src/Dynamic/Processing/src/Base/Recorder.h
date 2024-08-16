#pragma once

#include <Processing/src/Base/Sensor.h>
#include <Utility/Base/Data/Data.h>
#include <string>

namespace dyn::prc::base{class Sensor;}


namespace dyn::prc::base{

struct Recorder{
  //---------------------------

  virtual bool record_sensor(dyn::prc::base::Sensor* sensor, std::string path){return false;}

  std::string format = "";
  float size = 0;
  float ts_beg = 0;
  float ts_rec = 0;

  //---------------------------
};

}
