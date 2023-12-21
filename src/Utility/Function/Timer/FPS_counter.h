#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>


class FPS_counter
{
public:
  FPS_counter(int fps_max);
  ~FPS_counter();

  //Main function
  void update();

  inline float get_fps() const { return fps;}
  inline void set_fps_max(int value){this->fps_max = value;}
  inline int get_fps_max(){return fps_max;}

private:
  std::chrono::time_point<std::chrono::steady_clock> last_time;
  float fps = 0;
  int fps_max = 60;
};
