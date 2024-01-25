#pragma once

#include <Utility/Namespace.h>

namespace gui{class Node;}
class Text;


namespace gui::dev::editor{

class Editor : public utl::base::Panel
{
public:
  //Constructor / Destructor
  Editor(gui::Node* gui, bool* show_window, string name);
  ~Editor();

public:
  //Main function
  void design_panel();

private:
  utl::gui::editor::Text* editor;
};

}
