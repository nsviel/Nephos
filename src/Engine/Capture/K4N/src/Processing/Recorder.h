#pragma once

#include <Utility/Specific/common.h>

namespace k4n::structure{class Struct_k4n;}
namespace k4n::dev{class Sensor;}
namespace eng::scene{class Exporter;}
namespace format::ply{class Exporter;}


namespace k4n::processing{

class Recorder
{
public:
  //Constructor / Destructor
  Recorder(k4n::structure::Struct_k4n* struct_k4n);
  ~Recorder();

public:
  //Main function
  void start_thread();
  void run_thread();
  void stop_thread();

  //Subfunction
  void make_export_to_ply(k4n::dev::Sensor* sensor);

private:
  k4n::structure::Struct_k4n* struct_k4n;
  eng::scene::Exporter* sce_exporter;
  format::ply::Exporter* ply_exporter;

  std::thread thread;
  bool thread_running = false;
  bool thread_idle = true;
};

}
