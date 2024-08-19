#pragma once

namespace ctr{class Node;}
namespace ctr{class Structure;}


namespace ctr::gui{

class Render
{
public:
  //Constructor / Destructor
  Render(ctr::Node* node_control);
  ~Render();

public:
  //Main function
  void run_control();

  //Keyboard
  void control_keyboard();

private:
  ctr::Node* node_control;
  ctr::Structure* ctr_struct;
};

}
