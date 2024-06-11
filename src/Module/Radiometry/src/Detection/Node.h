#pragma once

#include <Utility/Specific/Common.h>

namespace rad{class Node;}
namespace rad::detection{class Structure;}
namespace rad::detection::sphere{class Process;}
namespace rad::detection::chart{class Process;}


namespace rad::detection{

enum Step{
  VALIDATION = 1,
  PROCESSING = 2,
};

enum Data{
  NO_DATA = 0,
  HAS_DATA = 3,
};

class Node
{
public:
  //Constructor / Destructor
  Node(rad::Node* node_radio);
  ~Node();

public:
  //Main function
  void init();
  void loop();

  inline rad::Node* get_node_radio(){return node_radio;}
  inline rad::detection::Structure* get_rad_struct(){return rad_struct;}
  inline rad::detection::sphere::Process* get_sphere_process(){return sphere_process;}
  inline rad::detection::chart::Process* get_chart_process(){return chart_process;}

private:
  rad::Node* node_radio;
  rad::detection::Structure* rad_struct;
  rad::detection::sphere::Process* sphere_process;
  rad::detection::chart::Process* chart_process;
};

}
