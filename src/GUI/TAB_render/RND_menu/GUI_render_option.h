#ifndef GUI_OPION_H
#define GUI_OPION_H

#include <Specific/common.h>
#include <RES_base/BASE_panel.h>

class GUI;
class Param;
class VK_engine;
class VK_struct;


class GUI_render_option : public BASE_panel
{
public:
  //Constructor / Destructor
  GUI_render_option(GUI* gui, bool* show_window, string name);
  ~GUI_render_option();

public:
  //Main function
  void design_panel();

  //Subfunctions
  void option_color();
  void option_fps();

private:
  GUI* gui;
  Param* param;
  VK_engine* vk_engine;
  VK_struct* vk_struct;

  int width;
};

#endif
