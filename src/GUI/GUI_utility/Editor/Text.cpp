#include "Text.h"

#include <GUI.h>
#include <GUI_main/Style/GUI_font.h>


namespace gui::editor{

//Constructor / Destructor
Text::Text(GUI* gui){
  //---------------------------

  this->gui_font = gui->get_gui_font();
  this->editor = new TextEditor();
  editor->SetPalette(editor->get_custom_palette());

  this->current_file_path = "";
  this->has_been_saved = true;
  this->status = "Saved";

  //---------------------------
}
Text::~Text(){}

//Main function
void Text::run_editor(){
  //---------------------------

  this->editor_status();
  this->editor_control();
  this->editor_render();

  //---------------------------
}

//Subfunction
void Text::editor_status(){
  //---------------------------

  bool has_text_changed = editor->IsTextChanged();
  if(has_text_changed && has_been_saved){
    this->status = "Saved";
    this->has_been_saved = false;
  }
  else if(has_text_changed && has_been_saved == false){
    this->status = "Modified";
  }

  //---------------------------
}
void Text::editor_control(){
  //---------------------------

  if(ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows)){
    ImGuiIO io = ImGui::GetIO();
    for(int i=0; i<IM_ARRAYSIZE(io.KeysDown); i++){
      //CTRL + S - save to file
      if(io.KeysDown[527] && ImGui::IsKeyPressed(ImGuiKey_S)){
        this->save_to_current_file();
        break;
      }
    }
  }

  //---------------------------
}
void Text::editor_render(){
  //---------------------------

  ImGuiIO& io = ImGui::GetIO();
  ImFont* font = gui_font->get_font_editor();
  ImGui::PushFont(font);
  editor->Render("Editor");
  ImGui::PopFont();

  //---------------------------
}

//Optionnal function
void Text::display_status(){
  //---------------------------

  ImVec4 color;
  if(status == "Saved"){
    color = ImVec4(0.4f,1.0f,0.4f,1.0f);
  }
  else if(status == "Modified"){
    color = ImVec4(1.0f,0.4f,0.4f,1.0f);
  }

  ImGui::TextColored(ImVec4(0.4f,0.4f,0.4f,1.0f), "Status: ");
  ImGui::SameLine();
  ImGui::TextColored(color, "%s", status.c_str());

  //---------------------------
}
void Text::load_from_file(string path){
  //---------------------------

  //Open file
  ifstream file;
  file.open(path.c_str());

  //Get first line
  string line;
  std::getline(file, line);
  string buffer = line;

  //Get following lines
  while(std::getline(file, line)){
    buffer = buffer + "\n" + line;
  }

  editor->SetText(buffer);

  this->current_file_path = path;

  //---------------------------
  editor->set_is_text_changed(false);
}
void Text::save_to_file(string path){
  //---------------------------

  string new_text = editor->GetText();

  ofstream file;
  file.open (path);
  file << new_text;
  file.close();

  //---------------------------
  this->has_been_saved = true;
  this->status = "Saved";
}
void Text::save_to_current_file(){
  //---------------------------

  string new_text = editor->GetText();

  ofstream file;
  file.open(current_file_path);
  file << new_text;
  file.close();

  //---------------------------
  this->has_been_saved = true;
  this->status = "Saved";
}
string Text::get_text(){
  //---------------------------

  string new_text = editor->GetText();

  //---------------------------
  return new_text;
}

}
