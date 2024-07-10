#pragma once

#include <Dynamic/src/Thread/Task.h>

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dyn::base{class Sensor;}
namespace dat::element{class Entity;}
namespace utl::thread{class Pool;}
namespace ope::color{class Colorizer;}


namespace dyn::cloud{

class Finalizer_test : public dyn::thread::Task
{
public:
  //Constructor / Destructor
  Finalizer_test(dyn::Node* node_dynamic);
  ~Finalizer_test();

public:
  //Main function
  void thread_task();

  //Subfunction
  void colorize_object(dyn::base::Sensor* sensor);
  void update_object(dyn::base::Sensor* sensor);

private:
  dyn::Structure* dyn_struct;
  dat::element::Entity* dat_entity;
  ope::color::Colorizer* ope_colorizer;
  utl::thread::Pool* thread_pool;

  bool thread_idle = true;
};

}
