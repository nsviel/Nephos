#pragma once

#include <Utility/Specific/Common.h>
#include <GUI/Namespace.h>

namespace dev::gui{class Node;}


namespace dev::gui{

class Menu
{
public:
  //Constructor / Destructor
  Menu(dev::gui::Node* tab_dev);
  ~Menu();

public:
  //Main function
  void run_tab_menu();

  //Subfunctions
  void open_panels();

private:
  dev::gui::Node* tab_dev;

};

}
