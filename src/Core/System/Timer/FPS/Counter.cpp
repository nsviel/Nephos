#include "Counter.h"


namespace sys::timer::fps{

// Constructor / Destructor
Counter::Counter(){
  //---------------------------

  this->last_time = std::chrono::steady_clock::now();

  //---------------------------
}

Counter::~Counter(){}

// Main function
float Counter::update(){
  //---------------------------

  auto now = std::chrono::steady_clock::now();
  auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(now - last_time).count();
  this->last_time = now;

  float current_fps = 1000000.0f / elapsed_time;

  // Add the current FPS to the FIFO queue
  fps_queue.push(current_fps);

  // Maintain the queue size at 10 (remove the oldest element if necessary)
  if(fps_queue.size() > 10){
    fps_queue.pop();
  }

  // Calculate and update the mean FPS
  mean_fps = calculate_mean_fps();

  //---------------------------
  return mean_fps;
}

float Counter::calculate_mean_fps(){
  //---------------------------

  if(fps_queue.empty()){
    return 0.0f;
  }

  // Create a temporary vector to hold the values of the queue
  std::vector<float> fps_vector(fps_queue.size());

  // Copy values from the queue to the vector
  size_t i = 0;
  while(!fps_queue.empty()){
    fps_vector[i++] = fps_queue.front();
    fps_queue.pop();
  }

  // Calculate the mean of the FPS values in the vector
  float sum = std::accumulate(fps_vector.begin(), fps_vector.end(), 0.0f);

  // Restore values back to the queue
  for(float value : fps_vector){
    fps_queue.push(value);
  }

  //---------------------------
  return sum / static_cast<float>(fps_queue.size());
}

}
