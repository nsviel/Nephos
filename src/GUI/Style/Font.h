#pragma once

#include <Utility/Specific/common.h>

namespace gui{class Node;}
namespace vk::main{class Imgui;}


namespace gui::style{

class Font
{
public:
  //Constructor / Destructor
  Font(gui::Node* gui);
  ~Font();

public:
  //Main functions
  void init_font();

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
  vk::main::Imgui* vk_imgui;

  vector<ImFont*> vec_font_editor;
  vector<ImFont*> vec_font_gui;
  ImFont* font_editor;
  ImFont* font_gui;
  ImFont* font_small;
};

}
