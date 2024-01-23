#pragma once

#include <Utility/Specific/common.h>
#include <Utility/GUI/Base/Panel.h>
#include <Utility/GUI/Editor/Namespace.h>

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
