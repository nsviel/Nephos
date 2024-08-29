#pragma once

#include <thread>

namespace vld{class Structure;}
namespace vld::processing{class Player;}


namespace vld::thread{

class Playback
{
public:
  //Constructor / Destructor
  Playback(vld::Structure* vld_struct);
  ~Playback();

public:
  //Main function
  void start_thread();
  void run_thread();
  void stop_thread();

  //Subfunction
  void manage_pause();

private:
  vld::Structure* vld_struct;
  vld::processing::Player* vld_player;

  std::thread thread;
  bool thread_running = false;
  bool thread_idle = true;
  bool thread_paused = false;
};

}
