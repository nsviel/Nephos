#pragma once

#include <Utility/Specific/Common.h>

namespace vld::structure{class Main;}
namespace vld{class Player;}


namespace vld::thread{

class Playback
{
public:
  //Constructor / Destructor
  Playback(vld::structure::Main* vld_struct);
  ~Playback();

public:
  //Main function
  void start_thread();
  void run_thread();
  void stop_thread();

private:
  vld::structure::Main* vld_struct;
  vld::Player* vld_player;

  std::thread thread;
  bool thread_running = false;
  bool thread_idle = true;
};

}
