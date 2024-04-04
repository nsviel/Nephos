#pragma once

// Server side implementation of UDP client-server model

#include <Utility/Specific/Common.h>
#include <thread>

namespace vld{class Frame;}
namespace vld{class Server;}
namespace vld::parser{class VLP16;}


namespace vld{

class Capture
{
public:
  //Constructor / Destructor
  Capture();
  ~Capture();

public:
  //Main function
  void start_thread(int port);
  void run_thread(int port);
  void stop_thread();

  inline string* get_lidar_ip(){return &lidar_ip;}

private:
  vld::Frame* velo_frame;
  vld::Server* velo_server;
  vld::parser::VLP16* parser_vlp16;

  utl::entity::Object* object;
  utl::file::Entity utl_file;

  string lidar_ip;
  bool thread_running;
  std::thread thread;
};

}
