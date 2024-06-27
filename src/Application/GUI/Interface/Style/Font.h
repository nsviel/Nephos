#pragma once

#include <Utility/Specific/Common.h>

namespace gui{class Node;}


namespace gui::style{

class Font
{
public:
  //Constructor / Destructor
  Font(gui::Node* gui);
  ~Font();

public:
  //Main function
  void init_font();

  //Subfunction
  void combo_font_gui();
  void combo_font_editor();
  void gui_select_font();

  inline ImFont* get_font_editor(){return font_editor;}
  inline ImFont* get_font_current(){return font_gui;}
  inline ImFont* get_font_small(){return font_small;}
  inline std::vector<ImFont*> get_vec_font_editor(){return vec_font_editor;}
  inline std::vector<ImFont*> get_vec_font_gui(){return vec_font_gui;}
  inline void set_current_font(ImFont* font){if(font!=nullptr)ImGui::GetIO().FontDefault = font;}
  inline void set_editor_font(ImFont* font){if(font!=nullptr)this->font_editor = font;}

private:
  std::vector<ImFont*> vec_font_editor;
  std::vector<ImFont*> vec_font_gui;
  ImFont* font_editor;
  ImFont* font_gui;
  ImFont* font_small;
};

}
