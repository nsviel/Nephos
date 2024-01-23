#pragma once

#include <Utility/Specific/common.h>
#include <Utility/Base/GUI/Panel.h>
#include <Utility/GUI/Editor/Namespace.h>

class GUI;
class Text;


namespace gui::dev::editor{

class Editor : public utl::base::Panel
{
public:
  //Constructor / Destructor
  Editor(GUI* gui, bool* show_window, string name);
  ~Editor();

public:
  //Main function
  void design_panel();

private:
  utl::gui::editor::Text* editor;
};

}
