#pragma once

#include <Utility/Base/Data/Data.h>
#include <thread>

namespace vld{class Node;}
namespace vld{class Structure;}
namespace vld::processing{class Player;}
namespace vld::processing{class Frame;}
namespace vld::utils{class Server;}
namespace vld::parser{class VLP16;}
namespace vld::main{class Data;}
namespace vld::thread{class Screenshot;}
namespace dat::gph{class Graph;}
namespace io::imp{class Importer;}
namespace dat::elm{class Set;}


namespace vld::thread{

class Server
{
public:
  //Constructor / Destructor
  Server(vld::Node* node_vld);
  ~Server();

public:
  //Main function
  void start_thread();
  void run_thread();
  void stop_thread();

  //Subfunction
  void capture_data();
  void update_object(utl::base::Data& data);

private:
  dat::gph::Graph* dat_graph;
  io::imp::Importer* io_loader;
  dat::elm::Set* dat_set;

  vld::Structure* vld_struct;
  vld::processing::Player* vld_player;
  vld::processing::Frame* vld_frame;
  vld::utils::Server* vld_server;
  vld::parser::VLP16* vld_vlp16;
  vld::main::Data* vld_data;
  vld::thread::Screenshot* thread_screenshot;

  utl::base::Data utl_file;
  std::thread thread;
  bool thread_running = false;
  bool thread_idle = true;
  bool thread_paused = false;
  int frame_ID = 0;
};

}
