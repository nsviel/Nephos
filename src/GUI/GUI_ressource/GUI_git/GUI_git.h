#ifndef GUI_GIT_H
#define GUI_GIT_H

#include <ELE_specific/common.h>

class GUI_font;
class GUI;
class UTL_git;


class GUI_git
{
public:
  //Constructor / Destructor
  GUI_git(GUI* gui);
  ~GUI_git();

public:
  //Main functions
  void design_panel();

  //Subfunction
  void draw_information();
  void draw_branches();

private:
  GUI_font* gui_font;
  UTL_git* git;
};

#endif
