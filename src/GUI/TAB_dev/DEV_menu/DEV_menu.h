#pragma once

#include "../DEV_nsp.h"
#include <UTL_specific/common.h>


namespace dev{

class DEV_menu
{
public:
  //Constructor / Destructor
  DEV_menu(DEV_panel* panel);
  ~DEV_menu();

public:
  //Main function
  void run_tab_menu();

  //Subfunctions
  void open_panels();

private:
  dev::DEV_panel* dev_panel;

};

}


#endif
