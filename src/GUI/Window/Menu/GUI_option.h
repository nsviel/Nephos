#ifndef GUI_OPION_H
#define GUI_OPION_H

#include <Specific/common.h>

class GUI;
class Param;
class VK_engine;
class VK_struct;


class GUI_option
{
public:
  //Constructor / Destructor
  GUI_option(GUI* gui);
  ~GUI_option();

public:
  //Main function
  void design_option();

  //Subfunctions
  void option_color();
  void option_font();
  void option_fps();

private:
  GUI* gui;
  Param* param;
  VK_engine* vk_engine;
  VK_struct* vk_struct;

  int width;
};

#endif
