#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>


class FPS_counter
{
public:
  FPS_counter();
  ~FPS_counter();

  //Main function
  float update();

  inline float get_fps() const { return fps;}

private:
  std::chrono::time_point<std::chrono::steady_clock> last_time;
  float fps = 0;
};
