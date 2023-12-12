#pragma once

#include <Utility/Specific/common.h>


namespace gui::plot{

class Plotting
{
public:
  //Constructor / Destructor
  Plotting();
  ~Plotting();

public:
  //Main function
  void open_file();

  //Subfunction
  void implot_style();

private:
};

}
