#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <queue>
#include <numeric>


namespace sys::timer::fps{

class Counter
{
public:
  Counter();
  ~Counter();

  //Main function
  float update();
  float calculate_mean_fps();

  inline float get_fps() const { return mean_fps;}

private:
  std::chrono::time_point<std::chrono::steady_clock> last_time;
  std::queue<float> fps_queue;
  float mean_fps = 0;
};

}
