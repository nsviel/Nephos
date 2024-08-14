#pragma once

#include <Dynamic/src/Base/Recorder.h>
#include <thread>
#include <string>

namespace k4n::base{class Sensor;}


namespace k4n::capture{

class Recorder : public dyn::base::Recorder
{
public:
  //Constructor / Destructor
  Recorder();
  ~Recorder();

public:
  //Main function
  bool record_sensor(dyn::base::Sensor* sensor, std::string path);

  //Subfunction
  void export_start(k4n::base::Sensor* sensor, std::string path);
  void export_record(k4n::base::Sensor* sensor, std::string path);
  void export_stop(k4n::base::Sensor* sensor);

private:
  std::thread thread;
  bool thread_running = false;
};

}
