#pragma once

#include <Utility/Base/Type/Node.h>
#include <Utility/Specific/Common.h>

namespace prf{class Manager;}
namespace prf::hardware{class Profiler;}
namespace prf::gui{class Panel;}


namespace prf{

class Node : public utl::base::Node
{
public:
  Node();
  ~Node();

public:
  //Main function
  void init();
  void gui();
  void loop();

  inline prf::Manager* get_prf_manager(){return prf_manager;}

private:
  prf::Manager* prf_manager;
  prf::hardware::Profiler* prf_hardware;
  prf::gui::Panel* gui_panel;
};

}
