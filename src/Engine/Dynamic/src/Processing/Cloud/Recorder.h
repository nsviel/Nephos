#pragma once

#include <Loader/src/Base/Recorder.h>
#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace dat::base{class Entity;}
namespace utl::thread{class Pool;}
namespace ldr::io{class Exporter;}


namespace dyn::cloud{

class Recorder : public ldr::base::Recorder
{
public:
  //Constructor / Destructor
  Recorder(dyn::Node* node_dynamic);
  ~Recorder();

public:
  //Main function
  void start_thread(dat::base::Entity* entity);
  void run_thread(dat::base::Entity* entity);
  void wait_thread();

  //Subfunction
  void make_export_to_ply(dat::base::Entity* entity, std::string path_dir, std::string path_name);

private:
  utl::thread::Pool* thread_pool;
  ldr::io::Exporter* ldr_exporter;

  bool idle = true;
};

}
