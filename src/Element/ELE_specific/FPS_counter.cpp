#include "FPS_counter.h"


//Constructor / Destructor
FPS_counter::FPS_counter(int nb_values){
  //---------------------------

  this->history_size = nb_values;
  this->frame_times = std::vector<int>(nb_values, 0);

  //---------------------------
}
FPS_counter::~FPS_counter(){}

//Main function
void FPS_counter::update(){
  //---------------------------

  auto now = std::chrono::steady_clock::now();
  auto frameDuration = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdateTime_).count();
  lastUpdateTime_ = now;

  frame_times[currentIndex_] = frameDuration;
  currentIndex_ = (currentIndex_ + 1) % history_size;

  this->update_moving_average();
  this->control_max_fps();

  //---------------------------
  cpt_frame++;
}
void FPS_counter::update_moving_average(){
  //---------------------------

  if(cpt_frame > history_size){
    average_fps = 0;
    for (int i = 0; i < history_size; ++i){
      average_fps += frame_times[i];
    }
    average_fps /= history_size;
    this->fps = 1000000.0f / average_fps;
  }
  else{
    average_fps = 0;
  }

  //---------------------------
}
void FPS_counter::control_max_fps(){
  if(cpt_frame < history_size) return;
  //---------------------------

  int minFrameDuration = 1000000.0f / max_fps; // Minimum frame duration in microseconds

  // Calculate the time to sleep to achieve the desired FPS
  int sleepTime = minFrameDuration - average_fps;

  if (sleepTime > 0) {
    std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
  }

  //---------------------------
}
