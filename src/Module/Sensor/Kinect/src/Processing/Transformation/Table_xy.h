#pragma once

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::base{class Sensor;}


namespace k4n::processing::image{

class Table_xy
{
public:
  //Constructor / Destructor
  Table_xy(k4n::Node* node_k4n);
  ~Table_xy();

public:
  //Main function
  void find_color_to_depth_table(k4n::base::Sensor* sensor);

private:
  k4n::Structure* k4n_struct;
};

}
