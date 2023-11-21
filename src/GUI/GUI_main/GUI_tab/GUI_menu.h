#ifndef GUI_MENU_H
#define GUI_MENU_H

#include <UTL_specific/common.h>

class GUI;
class GUI_font;
class GUI_git;


class GUI_menu
{
public:
  //Constructor / Destructor
  GUI_menu(GUI* gui);
  ~GUI_menu();

public:
  //Menu function
  void menu();
  void menu_option();
  void menu_demo();
  void menu_git();

private:
  GUI* gui;
  GUI_font* gui_font;
  GUI_git* gui_git;

  bool show_demo;
};

#endif
