#pragma once

#include <Utility/Specific/Common.h>

namespace vld::structure{class Main;}
namespace vld::main{class Player;}


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

  //Subfunction
  void manage_pause();

private:
  vld::structure::Main* vld_struct;
  vld::main::Player* vld_player;

  std::thread thread;
  bool thread_running = false;
  bool thread_idle = true;
  bool thread_paused = false;
};

}
