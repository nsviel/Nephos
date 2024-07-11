#pragma once

#include <Dynamic/src/Thread/Task.h>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::base{class Sensor;}


namespace k4n::processing::image{

class Table_xy : public dyn::thread::Task
{
public:
  //Constructor / Destructor
  Table_xy(k4n::Node* node_k4n);
  ~Table_xy();

public:
  //Main function
  void thread_function();

  //Subfunction
  void table_color_to_depth(k4n::base::Sensor* sensor);
  void convert_table_to_glm(k4n::base::Sensor* sensor);

private:
  k4n::Structure* k4n_struct;
};

}
