#pragma once

#include <Utility/Specific/common.h>

namespace prf::gui{class Panel;}
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

private:
  prf::gui::Panel* gui_panel;
  prf::Manager* profiler;
};

}
