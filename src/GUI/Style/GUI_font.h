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
  ImFont* gui_combo_font(string title, ImFont* font_current);
  void gui_select_font();
  void gui_load_font();

  inline ImFont* get_font_editor(){return font_editor;}
  inline ImFont* get_font_current(){return ImGui::GetFont();}
  inline void set_current_font(ImFont* font){if(font!=nullptr)ImGui::GetIO().FontDefault = font;}
  inline void set_editor_font(ImFont* font){if(font!=nullptr)this->font_editor = font;}
private:
  VK_struct* vk_struct;

  ImFont* font_editor;
};

#endif
