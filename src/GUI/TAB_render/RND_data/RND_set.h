#ifndef GUI_SET_H
#define GUI_SET_H

#include <GUI_base/BASE_panel.h>
#include <ELE_specific/common.h>

class GUI;
class RND_panel;


class RND_set : public BASE_panel
{
public:
  //Constructor / Destructor
  RND_set(GUI* gui, bool* show_window, string name);
  ~RND_set();

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
