#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>


namespace utl::fps{

class FPS_control
{
public:
  FPS_control(int fps_max);
  ~FPS_control();

  //Main function
  void start();
  void stop();

  inline void set_fps_max(int value){this->fps_max = value;}
  inline int get_fps_max(){return fps_max;}

private:
  std::chrono::time_point<std::chrono::steady_clock> start_time;
  int fps_max = 60;
};

}
