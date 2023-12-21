#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <thread>


class FPS_counter
{
public:
  FPS_counter(int nb_values);
  ~FPS_counter();

  //Main function
  void update();
  void update_moving_average();
  void control_max_fps();

  inline float get_fps() const { return fps;}
  inline void set_fps_max(int value){this->max_fps = value;}
  inline int get_fps_max(){return max_fps;}

private:
  std::chrono::time_point<std::chrono::steady_clock> lastUpdateTime_;
  std::vector<int> frame_times;
  float fps = 0;
  int64_t average_fps = 0;
  int history_size;
  int max_fps = 60;
  int cpt_frame = 0;
  int currentIndex_ = 0;
};
