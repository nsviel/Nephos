#pragma once

#include <chrono>

namespace sys::timer{

typedef std::chrono::high_resolution_clock::time_point Timepoint;

class Chrono{
public:
  // Constructor / Destructor
  Chrono();
  ~Chrono();

public:
  // Timer operations
  sys::timer::Timepoint start_t();
  sys::timer::Timepoint get_time();
  float stop_s(sys::timer::Timepoint t1);
  float stop_ms(sys::timer::Timepoint t1);
  float stop_us(sys::timer::Timepoint t1);
  float stop_ns(sys::timer::Timepoint t1);
  double duration_s(sys::timer::Timepoint t1, sys::timer::Timepoint t2);

  // Time since epoch
  double get_time_start();
  double get_time_stop();

private:
  Timepoint t1;
  Timepoint t2;
};

}
