#pragma once

#include <Dynamic/src/Thread/Routine.h>

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dyn::base{class Sensor;}
namespace dat::base{class Entity;}
namespace dat::element{class Entity;}
namespace utl::thread::task{class Pool;}
namespace ope::color{class Colorizer;}


namespace dyn::cloud{

class Colorizer : public dyn::thread::Routine
{
public:
  //Constructor / Destructor
  Colorizer(dyn::Node* node_dynamic);
  ~Colorizer();

public:
  //Main function
  void thread_task();

  //Subfunction
  void colorize_object(dat::base::Entity* entity);
  void update_object(dat::base::Entity* entity);

private:
  dyn::Structure* dyn_struct;
  dat::element::Entity* dat_entity;
  ope::color::Colorizer* ope_colorizer;
  utl::thread::task::Pool* thread_pool;

  bool thread_idle = true;
};

}
