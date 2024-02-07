#pragma once

#include <Utility/Specific/common.h>

namespace prf::gui{class Panel;}
namespace prf{class Tasker;}
namespace prf{class Manager;}


namespace prf{

class Node : public utl::type::Node
{
public:
  Node();
  ~Node();

public:
  //Main function
  void init();
  void gui();

  inline prf::Manager* get_profiler(){return profiler;}
  inline prf::Tasker* get_tasker_cpu(){return tasker_cpu;}
  inline prf::Tasker* get_tasker_gpu(){return tasker_gpu;}
  inline prf::Tasker* get_tasker_cap(){return tasker_cap;}

private:
  prf::gui::Panel* gui_panel;
  prf::Tasker* tasker_cpu;
  prf::Tasker* tasker_gpu;
  prf::Tasker* tasker_cap;
  prf::Manager* profiler;
};

}
