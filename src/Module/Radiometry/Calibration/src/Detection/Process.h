#pragma once

namespace rad::cal{class Node;}
namespace rad::cal{class Structure;}
namespace rad::cal{class Detection;}
namespace dat::gph{class Selection;}


namespace rad::cal{

class Process
{
public:
  //Constructor / Destructor
  Process(rad::cal::Node* node_detection);
  ~Process();

public:
  //Main function
  void init();
  void loop();

  //Subfunction
  void step_detection();
  void step_measure();

private:
  rad::cal::Structure* rad_struct;
  rad::cal::Detection* rad_detection;
  dat::gph::Selection* gph_selection;
};

}
