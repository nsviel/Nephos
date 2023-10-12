#ifndef WIN_DATA_H
#define WIN_DATA_H

#include <Panel/BASE_panel.h>
#include <Specific/common.h>

class GUI;
class Panel;
class Scene;


class GUI_object : public BASE_panel
{
public:
  //Constructor / Destructor
  GUI_object(GUI* gui, bool* show_window, string name);
  ~GUI_object();

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
  Panel* panel;
  Scene* sceneManager;

  Object* object_selected;
  int item_width;
};

#endif
