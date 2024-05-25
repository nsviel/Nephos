#pragma once

#include <Loader/src/Base/Recorder.h>
#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::dev{class Master;}
namespace eng{class Node;}
namespace dat{class Graph;}
namespace k4n::dev{class Sensor;}
namespace utl::thread{class Pool;}
namespace ldr{class Exporter;}
namespace format::ply{class Exporter;}


namespace k4n::capture{

class Recorder : public ldr::base::Recorder
{
public:
  //Constructor / Destructor
  Recorder(k4n::Node* node_k4n);
  ~Recorder();

public:
  //Main function
  void start_thread(k4n::dev::Sensor* sensor);
  void run_thread(k4n::dev::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void make_export_to_ply(k4n::dev::Sensor* sensor);
  void make_export_to_mkv(k4n::dev::Sensor* sensor);

private:
  utl::thread::Pool* thread_pool;
  ldr::Exporter* ldr_exporter;
  format::ply::Exporter* ply_exporter;

  bool idle = true;
};

}
