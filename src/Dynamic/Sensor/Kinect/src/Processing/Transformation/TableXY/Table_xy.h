#pragma once

#include <k4a/k4a.hpp>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::base{class Sensor;}
namespace dat::img{class Storage;}
namespace utl::base{class Storage;}


namespace k4n::processing{

class Table_xy
{
public:
  //Constructor / Destructor
  Table_xy(k4n::Node* node_k4n);
  ~Table_xy();

public:
  //Main function
  void build_table_xy(k4n::base::Sensor& sensor);

  //Subfunction
  void build_color_texture(k4n::base::Sensor& sensor);
  void build_depth_texture(k4n::base::Sensor& sensor);
  void build_texture(k4n::base::Sensor& sensor, utl::base::Storage& storage, k4a_calibration_type_t calibration);

private:
  k4n::Structure* k4n_struct;
  dat::img::Storage* dat_storage;
};

}
