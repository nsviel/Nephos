#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>


namespace prf::fps{

class Control
{
public:
  Control(int fps_max);
  ~Control();

  //Main function
  void start_loop();
  void stop_loop();

  inline void set_fps_max(int value){this->fps_max = value;}
  inline int get_fps_max(){return fps_max;}

private:
  std::chrono::time_point<std::chrono::steady_clock> start_time;
  int fps_max = 60;
};

}
