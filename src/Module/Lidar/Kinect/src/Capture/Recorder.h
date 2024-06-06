#pragma once

#include <Dynamic/src/Base/Recorder.h>
#include <Utility/Specific/Common.h>

namespace k4n::structure{class Sensor;}


namespace k4n::capture{

class Recorder : public dyn::base::Recorder
{
public:
  //Constructor / Destructor
  Recorder();
  ~Recorder();

public:
  //Main function
  void record_sensor(dyn::base::Sensor* sensor, std::string path);

  //Subfunction
  void export_start(k4n::structure::Sensor* sensor, std::string path);
  void export_record(k4n::structure::Sensor* sensor, std::string path);
  void export_stop(k4n::structure::Sensor* sensor);

private:
  std::thread thread;
  bool thread_running = false;
};

}
