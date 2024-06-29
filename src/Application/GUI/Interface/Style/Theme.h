#pragma once

namespace gui{class Node;}


namespace gui::style{

class Theme
{
public:
  //Constructor / Destructor
  Theme(gui::Node* gui);
  ~Theme();

public:
  //Main function
  void init_theme();

  //Subfunction
  void theme_main();
  void theme_window();
  void theme_widget();

private:

};

}
