#pragma once

#include <Utility/UTL_specific/common.h>

class GUI;
class VK_imgui;


class GUI_font
{
public:
  //Constructor / Destructor
  GUI_font(GUI* gui);
  ~GUI_font();

public:
  //Main functions
  void init_gui_font();

  //Subfunction
  void combo_font_gui();
  void combo_font_editor();
  void gui_select_font();

  inline ImFont* get_font_editor(){return font_editor;}
  inline ImFont* get_font_current(){return font_gui;}
  inline ImFont* get_font_small(){return font_small;}
  inline vector<ImFont*> get_vec_font_editor(){return vec_font_editor;}
  inline vector<ImFont*> get_vec_font_gui(){return vec_font_gui;}
  inline void set_current_font(ImFont* font){if(font!=nullptr)ImGui::GetIO().FontDefault = font;}
  inline void set_editor_font(ImFont* font){if(font!=nullptr)this->font_editor = font;}

private:
  VK_imgui* vk_imgui;

  vector<ImFont*> vec_font_editor;
  vector<ImFont*> vec_font_gui;
  ImFont* font_editor;
  ImFont* font_gui;
  ImFont* font_small;
};
