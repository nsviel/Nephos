#pragma once

class Config;
namespace eng{class Node;}
namespace utl{class Node;}
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
  eng::Node* node_engine;
  utl::Node* node_utility;
  GUI* gui;
};
