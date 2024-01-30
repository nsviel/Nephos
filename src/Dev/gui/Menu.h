#pragma once

#include <Utility/Specific/common.h>
#include <GUI/Namespace.h>

namespace dev::gui{class Tab;}


namespace dev::gui{

class Menu
{
public:
  //Constructor / Destructor
  Menu(dev::gui::Tab* dev_tab);
  ~Menu();

public:
  //Main function
  void run_tab_menu();

  //Subfunctions
  void open_panels();

private:
  dev::gui::Tab* dev_tab;

};

}
