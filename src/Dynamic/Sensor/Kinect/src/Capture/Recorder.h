#pragma once

#include <Data/Base/Sensor/Recorder.h>
#include <thread>
#include <memory>
#include <string>

namespace k4n::base{class Sensor;}
namespace dat::base{class Sensor;}


namespace k4n::capture{

class Recorder : public dat::base::sensor::Recorder
{
public:
  //Constructor / Destructor
  Recorder();
  ~Recorder();

public:
  //Main function
  bool record_sensor(std::shared_ptr<dat::base::Sensor> sensor, std::string path);

  //Subfunction
  void export_start(std::shared_ptr<k4n::base::Sensor> sensor, std::string path);
  void export_record(std::shared_ptr<k4n::base::Sensor> sensor, std::string path);
  void export_stop(std::shared_ptr<k4n::base::Sensor> sensor);

private:
  std::thread thread;
  bool thread_running = false;
};

}
