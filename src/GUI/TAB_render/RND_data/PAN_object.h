#ifndef GUI_OBJECT_H
#define GUI_OBJECT_H

#include <RES_base/BASE_panel.h>
#include <ELE_specific/common.h>

class GUI;
class RND_panel;
class Scene;


class PAN_object : public BASE_panel
{
public:
  //Constructor / Destructor
  PAN_object(GUI* gui, bool* show_window, string name);
  ~PAN_object();

  //Main function
  void design_panel();

  //Sub functions
  void object_info(Object* object);
  void object_parameter(Object* object);

  //Primitive size
  void width_line(Object* object);
  void size_point(Object* object);

  inline void set_selected_object(Object* object){this->object_selected = object;}

private:
  RND_panel* gui_render_panel;
  Scene* sceneManager;

  Object* object_selected;
  int item_width;
};

#endif
