#pragma once

class Config;
class Utility;
class Engine;
class GUI;


class App_main
{
public:
  //Constructor / Destructor
  App_main();
  ~App_main();

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
