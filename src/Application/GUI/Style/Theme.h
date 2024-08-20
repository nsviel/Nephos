#pragma once

namespace gui{class Node;}


namespace gui::style{

class Theme
{
public:
  //Constructor / Destructor
  Theme(gui::Node* node_gui);
  ~Theme();

public:
  //Main function
  void init();

  //Subfunction
  void theme_main();
  void theme_window();
  void theme_widget();

private:

};

}
