#pragma once

#include <Loader/src/Base/Recorder.h>
#include <Utility/Specific/Common.h>

namespace k4n::structure{class Sensor;}


namespace k4n::capture{

class Recorder : public ldr::base::Recorder
{
public:
  //Constructor / Destructor
  Recorder();
  ~Recorder();

public:
  //Main function
  void start_thread(k4n::structure::Sensor* sensor, std::string path);
  void run_thread(k4n::structure::Sensor* sensor, std::string path);
  void wait_thread();

  //Subfunction
  void export_start(k4n::structure::Sensor* sensor, std::string path);
  void export_loop(k4n::structure::Sensor* sensor, std::string path);
  void export_stop(k4n::structure::Sensor* sensor);

private:
  std::thread thread;
  bool thread_running = false;
};

}
