#pragma once

#include <string>

namespace utl::timer::fps{class Counter;}
namespace utl::timer::fps{class Control;}
namespace prf::dynamic{class Task;}


namespace prf::dynamic{

class Tasker
{
public:
  //Constructor / Destructor
  Tasker(std::string name);
  ~Tasker();

public:
  //Main function
  void reset();
  void loop(int fps = -1);

  //Loop function
  void loop_begin(int fps = -1);
  void loop_end();

  //Task function
  void task_begin(std::string name, float time = -1);
  void task_end(const std::string& name, float time = -1, glm::vec4 color = {});

  //Subfunction
  prf::dynamic::Task* retrieve_task(const std::string& name);

public:
  std::string name = "";
  utl::improfil::Plot plot;
  std::string thread_ID = "";
  float fps = 0;

private:
  utl::timer::Chrono timer;
  utl::timer::fps::Counter* fps_counter;
  utl::timer::fps::Control* fps_control;

  utl::timer::Timepoint reference;
  std::vector<prf::dynamic::Task> vec_task_current;
  std::vector<prf::dynamic::Task> vec_task;
  bool is_fps_control = false;
};

}
