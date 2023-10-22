#ifndef WIN_BASE_H
#define WIN_BASE_H

#include <Specific/common.h>


class BASE_panel
{
public:
  //Constructor / Destructor
  BASE_panel(bool* show_window, string name);
  ~BASE_panel();

public:
  //Main function
  void run_panel();

  //Subfunction
  virtual void design_panel();

  inline void set_name(string value){this->name = value;}
  inline bool get_show_window(){return *show_window;}
  inline string get_name(){return name;}

private:
  string name;
  int item_width;
  bool* show_window;
};

#endif
