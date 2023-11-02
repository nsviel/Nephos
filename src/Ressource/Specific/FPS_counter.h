#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

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

private:
  int history_size;
  int max_fps = 60;
  int cpt_frame = 0;
  std::vector<int> frame_times;
  int currentIndex_ = 0;
  int64_t average_fps = 0;
  float fps;
  std::chrono::time_point<std::chrono::steady_clock> lastUpdateTime_;
};


#endif
