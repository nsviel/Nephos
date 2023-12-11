#pragma once

#include <UTL_specific/common.h>
#include <GUI_utility/Base_nsp.h>
#include <GUI_utility/Editor/Namespace.h>

class GUI;
class Text;


namespace gui::dev::editor{

class Editor : public gui::base::Panel
{
public:
  //Constructor / Destructor
  Editor(GUI* gui, bool* show_window, string name);
  ~Editor();

public:
  //Main function
  void design_panel();

private:
  gui::editor::Text* editor;
};

}
