#pragma once

#include <Utility/Namespace.h>

class Config;
namespace eng{class Node;}
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
  eng::Node* engine;
  utl::Node* utility;
  GUI* gui;
};
