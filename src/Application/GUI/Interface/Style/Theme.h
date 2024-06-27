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
  void color_window();
  void color_widget();

private:

};

}
