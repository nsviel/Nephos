#ifndef GUI_OPION_H
#define GUI_OPION_H

#include <ELE_specific/common.h>
#include <RES_base/BASE_panel.h>

class GUI;
class Param;


class RND_option : public BASE_panel
{
public:
  //Constructor / Destructor
  RND_option(GUI* gui, bool* show_window, string name);
  ~RND_option();

public:
  //Main function
  void design_panel();

  //Subfunctions
  void option_color();
  void option_fps();

private:
  GUI* gui;
  Param* param;

  int width;
};

#endif
