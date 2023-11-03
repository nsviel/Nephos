#ifndef GUI_SET_H
#define GUI_SET_H

#include <RES_base/BASE_panel.h>
#include <Specific/common.h>

class GUI;
class RND_panel;


class GUI_set : public BASE_panel
{
public:
  //Constructor / Destructor
  GUI_set(GUI* gui, bool* show_window, string name);
  ~GUI_set();

  //Main function
  void design_panel();

  //Sub functions
  void set_info(Set* set);
  void set_parameter(Set* set);

  inline void set_selected_set(Set* set){this->set_selected = set;}

private:
  RND_panel* gui_render_panel;

  Set* set_selected;
  int item_width;
};

#endif
