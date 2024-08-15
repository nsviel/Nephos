#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <thread>

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dat::elm{class Image;}
namespace dat::elm{class Glyph;}
namespace utl::base{class Data;}
namespace dyn::base{class Sensor;}
namespace ope::image{class Converter;}
namespace dat::atr::normal{class Structured;}
namespace dat::atr{class Location;}
namespace utl::thread::task{class Pool;}


namespace dyn::cloud{

class Normal
{
public:
  // Constructor / Destructor
  Normal(dyn::Node* node_dynamic);
  ~Normal();

public:
  //Main function
  void start_thread(dyn::base::Sensor* sensor);
  void run_thread(dyn::base::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void compute_normal(dyn::base::Sensor* sensor);
  void compute_image(dyn::base::Sensor* sensor);

private:
  dyn::Structure* dyn_struct;
  dat::elm::Image* dat_image;
  dat::elm::Glyph* dat_glyph;
  dat::atr::normal::Structured* ope_normal;
  ope::image::Converter* ope_converter;
  dat::atr::Location* atr_location;
  utl::thread::task::Pool* thread_pool;

  std::thread thread;
  bool thread_idle = true;
};

}
