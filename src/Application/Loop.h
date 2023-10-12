#ifndef LOOP_H
#define LOOP_H

class Window;
class Engine;
class GUI;


class Loop
{
public:
  //Constructor / Destructor
  Loop();
  ~Loop();

public:
  //Main functions
  void run();

  //Subfunction
  void init();
  void loop();
  void end();

private:
  Engine* engine;
  Window* window;
  GUI* gui;
};

#endif
