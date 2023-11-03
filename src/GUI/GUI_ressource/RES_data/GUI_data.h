#ifndef GUI_DATA_H
#define GUI_DATA_H

#include <ELE_specific/common.h>

class GUI;

class VK_engine;
class Struct_vulkan;


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
  VK_engine* vk_engine;
  Struct_vulkan* vk_struct;

  int width;
};

#endif
