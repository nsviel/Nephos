#pragma once

#include <imgui/editor/Text/editor_text.h>
#include <string>


namespace utl::gui::editor{

class Text
{
public:
  //Constructor / Destructor
  Text();
  ~Text();

public:
  //Main function
  void run_editor();

  //Subfunction
  void editor_status();
  void editor_control();
  void editor_render();

  //Optionnal function
  void display_status();
  void load_from_file(std::string path);
  void save_to_file(std::string path);
  void save_to_current_file();
  std::string get_text();

  inline std::string get_status(){return status;}
  inline bool is_text_changed(){return editor->IsTextChanged();}
  inline void set_read_only(bool value){editor->SetReadOnly(value);}
  inline void set_language(std::string value){editor->set_language_definition(value);}

private:
  TextEditor* editor;

  std::string status;
  std::string current_file_path;
  bool has_been_saved;
};

}
