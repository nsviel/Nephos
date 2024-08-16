#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <thread>

namespace dyn::prc{class Node;}
namespace dyn::prc{class Structure;}
namespace dat::elm{class Image;}
namespace dat::elm{class Glyph;}
namespace utl::base{class Data;}
namespace dyn::prc::base{class Sensor;}
namespace dat::img{class Converter;}
namespace dat::atr::normal{class Structured;}
namespace dat::atr{class Location;}
namespace sys::thread::task{class Pool;}


namespace dyn::prc::cloud{

class Normal
{
public:
  // Constructor / Destructor
  Normal(dyn::prc::Node* node_dynamic);
  ~Normal();

public:
  //Main function
  void start_thread(dyn::prc::base::Sensor* sensor);
  void run_thread(dyn::prc::base::Sensor* sensor);
  void wait_thread();

  //Subfunction
  void compute_normal(dyn::prc::base::Sensor* sensor);
  void compute_image(dyn::prc::base::Sensor* sensor);

private:
  dyn::prc::Structure* dyn_struct;
  dat::elm::Image* dat_image;
  dat::elm::Glyph* dat_glyph;
  dat::atr::normal::Structured* ope_normal;
  dat::img::Converter* ope_converter;
  dat::atr::Location* atr_location;
  sys::thread::task::Pool* thread_pool;

  std::thread thread;
  bool thread_idle = true;
};

}
