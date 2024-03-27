#pragma once

// Server side implementation of UDP client-server model

#include <Utility/Specific/Common.h>
#include <thread>

namespace velodyne{class Frame;}
namespace velodyne{class Server;}
namespace velodyne::parser{class VLP16;}


namespace velodyne{

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
  velodyne::Frame* velo_frame;
  velodyne::Server* velo_server;
  velodyne::parser::VLP16* parser_vlp16;

  utl::entity::Object* object;
  utl::file::Entity utl_file;

  string lidar_ip;
  bool thread_running;
  std::thread thread;
};

}
