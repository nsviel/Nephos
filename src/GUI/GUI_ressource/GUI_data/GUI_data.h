#ifndef GUI_DATA_H
#define GUI_DATA_H

#include <ELE_specific/common.h>

class GUI;


class GUI_data
{
public:
  //Constructor / Destructor
  GUI_data(GUI* gui);
  ~GUI_data();

public:
  //Main function
  void design_data();

  //Subfunction


private:
  GUI* gui;

  int width;
};

#endif
