#include "GUI_editor_text.h"


//Constructor / Destructor
GUI_editor_text::GUI_editor_text(){
  //---------------------------

  this->editor = new TextEditor();
  //---------------------------
}
GUI_editor_text::~GUI_editor_text(){}

//Main function
void GUI_editor_text::run_editor(){
  //---------------------------

  editor->Render("Editor");

  //---------------------------
}

//Subfunction
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

  //---------------------------
}
void GUI_editor_text::save_to_file(string path){
  //---------------------------

  string new_text = editor->GetText();

  ofstream file;
  file.open (path);
  file << new_text;
  file.close();

  //---------------------------
}
string GUI_editor_text::get_text(){
  //---------------------------

  string new_text = editor->GetText();

  //---------------------------
  return new_text;
}
