#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <queue>
#include <numeric>


namespace utl::fps{

typedef std::chrono::high_resolution_clock::time_point Timepoint;

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
  Timepoint last_time;
  std::queue<float> fps_queue;
  float mean_fps = 0;
};

}
