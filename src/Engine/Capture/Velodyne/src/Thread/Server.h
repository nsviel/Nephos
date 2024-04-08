#pragma once

#include <Utility/Specific/Common.h>

namespace eng::scene{class Database;}
namespace eng::scene{class Loader;}
namespace eng::scene{class Set;}
namespace vld{class Node;}
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
  Server(vld::Node* node_vld);
  ~Server();

public:
  //Main function
  void start_thread();
  void run_thread();
  void stop_thread();

  //Subfunction
  void capture_data();
  void create_object(utl::file::Data* data);

private:
  eng::scene::Database* sce_database;
  eng::scene::Loader* sce_loader;
  eng::scene::Set* sce_set;

  vld::structure::Main* vld_struct;
  vld::processing::Player* vld_player;
  vld::processing::Frame* vld_frame;
  vld::utils::Server* vld_server;
  vld::parser::VLP16* vld_vlp16;

  utl::file::Data utl_file;
  std::thread thread;
  bool thread_running = false;
  bool thread_idle = true;
  bool thread_paused = false;
  int frame_ID = 0;
};

}
