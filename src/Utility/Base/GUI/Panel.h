#pragma once

#include <Utility/Specific/common.h>


namespace utl::base{

class Panel
{
public:
  //Constructor / Destructor
  Panel(bool* show_window, string name);
  ~Panel();

public:
  //Main function
  void run_panel();

  //Subfunction
  virtual void design_panel();

  inline void set_name(string value){this->name = value;}
  inline bool get_show_window(){return *show_window;}
  inline string get_name(){return name;}

  string name;
  int item_width;
  bool* show_window;
};

}
