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
void GUI_editor_text::load_file(string path){
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
