#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::structure{class K4N;}
namespace k4n::dev{class Device;}
namespace utl::thread{class Pool;}
namespace ldr{class Exporter;}
namespace format::ply{class Exporter;}


namespace k4n::processing{

class Recorder
{
public:
  //Constructor / Destructor
  Recorder(k4n::Node* node_k4n);
  ~Recorder();

public:
  //Main function
  void start_thread(k4n::dev::Device* sensor);
  void run_thread(k4n::dev::Device* sensor);
  void wait_thread();

  //Subfunction
  void make_export_to_ply(k4n::dev::Device* sensor);
  void make_export_to_mkv(k4n::dev::Device* sensor);

private:
  utl::thread::Pool* thread_pool;
  k4n::structure::K4N* k4n_struct;
  ldr::Exporter* ldr_exporter;
  format::ply::Exporter* ply_exporter;

  bool idle = true;
};

}
