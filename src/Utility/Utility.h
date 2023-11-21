#ifndef UTILITY_H
#define UTILITY_H

#include <UTL_specific/common.h>

class Config;
class UTL_window;


class Utility
{
public:
  //Constructor / Destructor
  Utility(Config* config);
  ~Utility();

public:
  //Main function
  void init();
  void loop();
  void exit();

  inline UTL_window* get_utl_window(){return utl_window;}

private:
  UTL_window* utl_window;
};

#endif
