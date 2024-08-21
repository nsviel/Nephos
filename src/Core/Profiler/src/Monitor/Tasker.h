#pragma once

#include <Utility/System/Timer/Chronometer/Chrono.h>
#include <Utility/GUI/Plot/ImProfil/Plot.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace sys::timer{class Chronos;}
namespace sys::fps{class Counter;}
namespace sys::fps{class Control;}
namespace prf::monitor{class Task;}


namespace prf::monitor{

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
  void update();

  //Task function
  void task_begin(std::string name, float time = -1);
  void task_end(const std::string& name, float time = -1, glm::vec4 color = {});
  void add_task(const std::string& name, float ts_begin, float ts_end, glm::vec4 color = {});
  void remove_task(const std::string& name);

  //Subfunction
  prf::monitor::Task* find_task(const std::string& name);

  inline bool is_idle(){return vec_task.size() == 0;}

public:
  std::string name = "";
  utl::improfil::Plot plot;
  std::string thread_ID = "";
  float fps = 0;

private:
  sys::timer::Chrono* timer;
  sys::fps::Counter* fps_counter;
  sys::fps::Control* fps_control;

  sys::timer::Timepoint reference;
  std::vector<prf::monitor::Task> vec_task_buffer;
  std::vector<prf::monitor::Task> vec_task;
  bool is_fps_control = false;
};

}
