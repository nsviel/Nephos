#ifndef GUI_DEV_PANEL_H
#define GUI_DEV_PANEL_H

#include <Specific/common.h>

class GUI;
class GUI_code_editor;
class Struct_dev_panel;


class GUI_dev_panel
{
public:
  //Constructor / Destructor
  GUI_dev_panel(GUI* gui);
  ~GUI_dev_panel();

public:
  //Main functions
  void create_panels();
  void draw_panels();
  void open_panels();

  inline Struct_dev_panel* get_panel(){return struct_dev_panel;}

private:
  GUI* gui;
  Struct_dev_panel* struct_dev_panel;
  GUI_code_editor* gui_code_editor;
};

#endif
