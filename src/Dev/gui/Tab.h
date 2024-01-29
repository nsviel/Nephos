#pragma once

#include <Utility/Specific/common.h>

namespace dev::gui{class Menu;}


namespace dev::gui{

class Tab
{
public:
  //Constructor / Destructor
  Tab();
  ~Tab();

public:
  //Main functions
  void draw_tab();

  //Subfunction
  void run_editors();

private:
  dev::gui::Menu* menu;
};

}
