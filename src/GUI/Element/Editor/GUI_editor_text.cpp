#include "GUI_editor_text.h"

#include <GUI.h>
#include <Style/GUI_font.h>
#include <Element/Control/GUI_control_editor.h>


//Constructor / Destructor
GUI_editor_text::GUI_editor_text(GUI* gui){
  //---------------------------

  this->gui_font = gui->get_gui_font();
  this->editor = new TextEditor();
  this->control = new GUI_control_editor(this);
  editor->SetPalette(editor->get_custom_palette());

  this->current_file_path = "";
  this->has_been_saved = true;
  this->status = "Saved";

  //---------------------------
}
GUI_editor_text::~GUI_editor_text(){}

//Main function
void GUI_editor_text::run_editor(){
  //---------------------------

  this->check_status();

  //Editor control
  if(ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows)){
    control->run_control();
  }

  //Draw control
  ImGuiIO& io = ImGui::GetIO();
  ImFont* font = gui_font->get_font_editor();

  ImGui::PushFont(font);
  editor->Render("Editor");
  ImGui::PopFont();

  //---------------------------
}

//Subfunction
void GUI_editor_text::check_status(){
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
void GUI_editor_text::display_status(){
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
void GUI_editor_text::load_from_file(string path){
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
void GUI_editor_text::save_to_file(string path){
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
void GUI_editor_text::save_to_current_file(){
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
string GUI_editor_text::get_text(){
  //---------------------------

  string new_text = editor->GetText();

  //---------------------------
  return new_text;
}
