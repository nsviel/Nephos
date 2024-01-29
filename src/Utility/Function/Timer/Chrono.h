#pragma once

typedef decltype(std::chrono::high_resolution_clock::now()) timer_time;


namespace utl::timer{

class Chrono
{
public:
  //Constructor / Destructor
  Chrono(){}
  ~Chrono(){}

public:
  timer_time start_t(){
    this->t1 = std::chrono::high_resolution_clock::now();
    return t1;
  }
  timer_time get_time(){
    timer_time time = std::chrono::high_resolution_clock::now();
    return time;
  }
  float stop_s(timer_time t1){
    this->t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    return duration.count() / 1000.0f;
  }
  float stop_ms(timer_time t1){
    this->t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
    return duration.count() / 1000.0f;
  }
  float stop_us(timer_time t1){
    this->t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    return duration.count() / 1000.0f;
  }
  float stop_ns(timer_time t1){
    this->t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1);
    return duration.count();
  }
  double duration_s(timer_time t1, timer_time t2){
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
    return duration.count() / 1000000.0f;
  }

  inline double get_time_start() {
    double time = std::chrono::duration_cast<std::chrono::duration<double>>(t1.time_since_epoch()).count();
    return time;
  }
  inline double get_time_stop() {
    double time = std::chrono::duration_cast<std::chrono::duration<double>>(t2.time_since_epoch()).count();
    return time;
  }

private:
  std::chrono::high_resolution_clock::time_point t1;
  std::chrono::high_resolution_clock::time_point t2;
};

}
