#pragma once

#include <Utility/Specific/Common.h>

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

  inline prf::Manager* get_prf_manager(){return prf_manager;}

private:
  prf::gui::Panel* gui_panel;
  prf::Manager* prf_manager;
};

}
