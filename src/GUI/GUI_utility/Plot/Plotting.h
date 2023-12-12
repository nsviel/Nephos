#pragma once

#include <Utility/Specific/common.h>

class GUI;


namespace gui::plot{

class Plotting
{
public:
  //Constructor / Destructor
  Plotting(GUI* gui);
  ~Plotting();

public:
  //Main function
  void open_file();

  //Subfunction
  void implot_style();

private:
};

}
