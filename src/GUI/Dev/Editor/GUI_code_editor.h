#ifndef GUI_CODE_EDITOR_H
#define GUI_CODE_EDITOR_H

#include <Specific/common.h>
#include <Ressource/Base/BASE_panel.h>

class GUI;
class GUI_editor_text;


class GUI_code_editor : public BASE_panel
{
public:
  //Constructor / Destructor
  GUI_code_editor(GUI* gui, bool* show_window, string name);
  ~GUI_code_editor();

public:
  //Main function
  void design_panel();

private:
  GUI_editor_text* editor;
};

#endif
