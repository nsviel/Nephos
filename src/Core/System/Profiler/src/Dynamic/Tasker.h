#pragma once

#include <Utility/GUI/Plot/ImProfil/Plot.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

namespace utl::timer{class Chronos;}
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
  void update();

  //Task function
  void task_begin(std::string name, float time = -1);
  void task_end(const std::string& name, float time = -1, glm::vec4 color = {});
  void add_task(const std::string& name, float ts_begin, float ts_end, glm::vec4 color = {});
  void remove_task(const std::string& name);

  //Subfunction
  prf::dynamic::Task* find_task(const std::string& name);

  inline bool is_idle(){return vec_task.size() == 0;}

public:
  std::string name = "";
  utl::improfil::Plot plot;
  std::string thread_ID = "";
  float fps = 0;

private:
  utl::timer::Chrono* timer;
  utl::timer::fps::Counter* fps_counter;
  utl::timer::fps::Control* fps_control;

  utl::timer::Timepoint reference;
  std::vector<prf::dynamic::Task> vec_task_buffer;
  std::vector<prf::dynamic::Task> vec_task;
  bool is_fps_control = false;
};

}
