#pragma once

#include <chrono>


namespace sys::timer{

typedef std::chrono::high_resolution_clock::time_point Timepoint;

class Chrono
{
public:
  //Constructor / Destructor
  Chrono(){}
  ~Chrono(){}

public:
  sys::timer::Timepoint start_t(){
    this->t1 = std::chrono::high_resolution_clock::now();
    return t1;
  }
  sys::timer::Timepoint get_time(){
    sys::timer::Timepoint time = std::chrono::high_resolution_clock::now();
    return time;
  }
  float stop_s(sys::timer::Timepoint t1){
    this->t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    return duration.count() / 1000.0f;
  }
  float stop_ms(sys::timer::Timepoint t1){
    this->t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
    return duration.count() / 1000.0f;
  }
  float stop_us(sys::timer::Timepoint t1){
    this->t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    return duration.count() / 1000.0f;
  }
  float stop_ns(sys::timer::Timepoint t1){
    this->t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    return duration.count();
  }
  double duration_s(sys::timer::Timepoint t1, sys::timer::Timepoint t2){
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
    return duration.count() / 1000000.0f;
  }

  inline double get_time_start(){
    double time = std::chrono::duration_cast<std::chrono::duration<double>>(t1.time_since_epoch()).count();
    return time;
  }
  inline double get_time_stop(){
    double time = std::chrono::duration_cast<std::chrono::duration<double>>(t2.time_since_epoch()).count();
    return time;
  }

private:
  Timepoint t1;
  Timepoint t2;
};

}
