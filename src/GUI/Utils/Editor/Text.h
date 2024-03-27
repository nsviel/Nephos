#pragma once

#include <Utility/Specific/Common.h>
#include <imgui/editor/Text/editor_text.h>


namespace utl::gui::editor{

class Text
{
public:
  //Constructor / Destructor
  Text();
  ~Text();

public:
  //Main functions
  void run_editor();

  //Subfunction
  void editor_status();
  void editor_control();
  void editor_render();

  //Optionnal function
  void display_status();
  void load_from_file(string path);
  void save_to_file(string path);
  void save_to_current_file();
  string get_text();

  inline string get_status(){return status;}
  inline bool is_text_changed(){return editor->IsTextChanged();}
  inline void set_read_only(bool value){editor->SetReadOnly(value);}
  inline void set_language(string value){editor->set_language_definition(value);}

private:
  TextEditor* editor;

  string status;
  string current_file_path;
  bool has_been_saved;
};

}
