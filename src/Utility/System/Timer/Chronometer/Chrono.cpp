#include "Chrono.h"

namespace sys::timer{

// Constructor / Destructor
Chrono::Chrono(){}
Chrono::~Chrono(){}

// Timer operations
sys::timer::Timepoint Chrono::start_t(){
  this->t1 = std::chrono::high_resolution_clock::now();
  return t1;
}
sys::timer::Timepoint Chrono::get_time(){
  sys::timer::Timepoint time = std::chrono::high_resolution_clock::now();
  return time;
}
float Chrono::stop_s(sys::timer::Timepoint t1){
  this->t2 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
  return duration.count() / 1000.0f;
}
float Chrono::stop_ms(sys::timer::Timepoint t1){
  this->t2 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
  return duration.count() / 1000.0f;
}
float Chrono::stop_us(sys::timer::Timepoint t1){
  this->t2 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
  return duration.count() / 1000.0f;
}
float Chrono::stop_ns(sys::timer::Timepoint t1){
  this->t2 = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
  return duration.count();
}
double Chrono::duration_s(sys::timer::Timepoint t1, sys::timer::Timepoint t2){
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
  return duration.count() / 1000000.0f;
}

// Time since epoch
double Chrono::get_time_start(){
  double time = std::chrono::duration_cast<std::chrono::duration<double>>(t1.time_since_epoch()).count();
  return time;
}
double Chrono::get_time_stop(){
  double time = std::chrono::duration_cast<std::chrono::duration<double>>(t2.time_since_epoch()).count();
  return time;
}

}
