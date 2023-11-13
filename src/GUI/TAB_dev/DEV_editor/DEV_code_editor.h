#ifndef GUI_CODE_EDITOR_H
#define GUI_CODE_EDITOR_H

#include <UTL_specific/common.h>
#include <GUI_base/BASE_panel.h>

class GUI;
class EDI_text;


class DEV_code_editor : public BASE_panel
{
public:
  //Constructor / Destructor
  DEV_code_editor(GUI* gui, bool* show_window, string name);
  ~DEV_code_editor();

public:
  //Main function
  void design_panel();

private:
  EDI_text* editor;
};

#endif
