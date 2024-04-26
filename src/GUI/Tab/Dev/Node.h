#pragma once

#include <Utility/Specific/Common.h>

namespace dev::gui{class Menu;}


namespace dev::gui{

class Node
{
public:
  //Constructor / Destructor
  Node();
  ~Node();

public:
  //Main functions
  void draw_tab();

  //Subfunction
  void run_editors();

private:
  dev::gui::Menu* menu;
};

}
