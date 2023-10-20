#ifndef GUI_FONT_H
#define GUI_FONT_H

#include <Specific/common.h>

class Engine;
class VK_struct;


class GUI_font
{
public:
  //Constructor / Destructor
  GUI_font(Engine* engine);
  ~GUI_font();

public:
  //Main functions
  void init_gui_font();

  //Subfunction
  void gui_select_font();
  void gui_load_font();

  inline ImFont* get_font_editor(){return font_editor;}

private:
  VK_struct* vk_struct;

  ImFont* font_editor;
};

#endif
