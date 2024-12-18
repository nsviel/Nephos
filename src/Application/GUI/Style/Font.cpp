#include "Font.h"

#include <GUI/Namespace.h>
#include <fontawesome/IconsFontAwesome6.h>


namespace gui::style{

//Constructor / Destructor
Font::Font(gui::Node* node_gui){
  //---------------------------

  //---------------------------
}
Font::~Font(){}

//Main function
void Font::init(){
  //---------------------------

  //this->gui_select_font();

  //---------------------------
}

//Subfunction
void Font::gui_select_font(){
  ImGuiIO io = ImGui::GetIO();
  //---------------------------

  static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };

  //Configuration - texte
  ImFontConfig config_text;
  config_text.GlyphExtraSpacing.x = 1.0f;

  //Configuration - texte
  ImFontConfig config_editor;
  config_editor.GlyphExtraSpacing.x = 2.0f;
  config_editor.OversampleH = 4.0f;
  config_editor.OversampleV = 4.0f;

  //Configuration - icon
  ImFontConfig config_icon;
  config_icon.MergeMode = true;
  config_icon.GlyphMinAdvanceX = 15.0f; //Monospace icons

  //Load all droidsans font with size from 13 to 23
  float font_size;
  font_size = 10.0f;
  for(int i=0; i<15; i++){
    ImFont* font = io.Fonts->AddFontFromFileTTF("../media/font/DroidSans.ttf", font_size, &config_text);
    io.Fonts->AddFontFromFileTTF("../media/font/fontawesome-webfont.ttf", font_size - 0.5f, &config_icon, icons_ranges);
    if(i == 0) this->font_gui = font;
    font_size += 1.0f;
    this->vec_font_gui.push_back(font);
  }

  font_size = 13.0f;
  for(int i=0; i<10; i++){
    ImFont* font = io.Fonts->AddFontFromFileTTF("../media/font/DroidSans.ttf", font_size, &config_editor);
    if(i == 0) this->font_editor = font;
    font_size += 1.0f;
    this->vec_font_editor.push_back(font);
  }

  //Buid the font database
  io.Fonts->Build();

  //Setup fonts
  this->font_gui = vec_font_gui[3];
  this->font_small = vec_font_gui[0];
  ImGui::GetIO().FontDefault = font_gui;

  //---------------------------
}
void Font::combo_font_gui(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  if(ImGui::BeginCombo("GUI##Font", font_gui->GetDebugName())){
    for(auto& font : vec_font_gui){
      ImGui::PushID((void*)font);
      if(ImGui::Selectable(font->GetDebugName(), font == font_gui)){
        ImGui::GetIO().FontDefault = font;
        this->font_gui = font;
      }
      ImGui::PopID();
    }
    ImGui::EndCombo();
  }

  //---------------------------
}
void Font::combo_font_editor(){
  ImGuiIO& io = ImGui::GetIO();
  //---------------------------

  if(ImGui::BeginCombo("Editor##Font", font_editor->GetDebugName())){
    for(auto& font : vec_font_editor){
      ImGui::PushID((void*)font);
      if(ImGui::Selectable(font->GetDebugName(), font == font_editor)){
        this->font_editor = font;
      }
      ImGui::PopID();
    }
    ImGui::EndCombo();
  }

  //---------------------------
}

}
