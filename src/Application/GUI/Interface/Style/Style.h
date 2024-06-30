#pragma once

namespace gui{class Node;}


namespace gui::style{

class Style
{
public:
  //Constructor / Destructor
  Style(gui::Node* gui);
  ~Style();

public:
  //Main function
  void init();

  //Subfunction
  void style_window();

private:
};

}
