#pragma once

#include <Loader/src/Base/Exporter.h>
#include <Utility/Specific/Common.h>

namespace dyn{class Node;}
namespace dat::base{class Entity;}
namespace utl::thread{class Pool;}
namespace ldr{class Exporter;}
namespace format::ply{class Exporter;}


namespace dyn::processing{

class Exporter : public ldr::base::Exporter
{
public:
  //Constructor / Destructor
  Exporter(dyn::Node* node_dynamic);
  ~Exporter();

public:
  //Main function
  void start_thread(dat::base::Entity* entity);
  void run_thread(dat::base::Entity* entity);
  void wait_thread();

  //Subfunction
  void make_export_to_ply(dat::base::Entity* entity, std::string path_dir, std::string path_name);

private:
  utl::thread::Pool* thread_pool;
  ldr::Exporter* ldr_exporter;
  format::ply::Exporter* ply_exporter;

  bool idle = true;
};

}
