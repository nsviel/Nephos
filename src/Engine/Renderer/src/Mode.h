#pragma once

namespace eng{class Node;}


namespace itf::render{

class Mode
{
public:
  //Constructor / Destructor
  Mode(eng::Node* node_engine);
  ~Mode();

public:
  //Main function
  void mode_visualization();

private:

};

}
