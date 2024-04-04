#pragma once

#include <Utility/Specific/Common.h>

namespace vld::structure{class Main;}
namespace vld::processing{class Player;}
namespace vld::processing{class Frame;}
namespace vld::utils{class Server;}
namespace vld::parser{class VLP16;}


namespace vld::thread{

class Server
{
public:
  //Constructor / Destructor
  Server(vld::structure::Main* vld_struct);
  ~Server();

public:
  //Main function
  void start_thread();
  void run_thread();
  void stop_thread();

  //Subfunction
  void capture_data();

private:
  vld::structure::Main* vld_struct;
  vld::processing::Player* vld_player;
  vld::processing::Frame* vld_frame;
  vld::utils::Server* vld_server;
  vld::parser::VLP16* vld_vlp16;

  utl::file::Entity utl_file;
  std::thread thread;
  bool thread_running = false;
  bool thread_idle = true;
  bool thread_paused = false;
  bool new_data = false;
};

}
