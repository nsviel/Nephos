#ifndef APP_MAIN_H
#define APP_MAIN_H

class Config;
class Utility;
class Engine;
class GUI;


class APP_main
{
public:
  //Constructor / Destructor
  APP_main();
  ~APP_main();

public:
  //Main functions
  void run();

  //Subfunction
  void init();
  void loop();
  void end();

private:
  Config* config;
  Engine* engine;
  Utility* utility;
  GUI* gui;
};

#endif
