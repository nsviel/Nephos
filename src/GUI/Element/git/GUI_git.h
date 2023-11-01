#ifndef GUI_GIT_H
#define GUI_GIT_H

#include <Specific/common.h>

class GUI;
class Git;


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
  void draw_branches();

private:
  Git* git;
};

#endif
