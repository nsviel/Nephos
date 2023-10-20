#ifndef GUI_EDITOR_TEXT_H
#define GUI_EDITOR_TEXT_H

#include <Specific/common.h>
#include <imgui/editor/Text/editor_text.h>

class GUI_control_editor;


class GUI_editor_text
{
public:
  //Constructor / Destructor
  GUI_editor_text();
  ~GUI_editor_text();

public:
  //Main functions
  void run_editor();

  //Subfunction
  void check_status();
  void display_status();
  void load_from_file(string path);
  void save_to_file(string path);
  void save_to_current_file();
  string get_text();

  inline string get_status(){return status;}
  inline bool is_text_changed(){return editor->IsTextChanged();}

private:
  GUI_control_editor* control;
  TextEditor* editor;

  string status;
  string current_file_path;
  bool has_been_saved;
};

#endif
