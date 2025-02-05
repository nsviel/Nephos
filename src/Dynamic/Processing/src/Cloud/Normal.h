#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <vector>
#include <thread>

namespace dyn::prc{class Node;}
namespace dyn::prc{class Structure;}
namespace dat::img{class Image;}
namespace dat::elm{class Glyph;}
namespace utl::base{class Data;}
namespace dat::base{class Sensor;}
namespace dat::img{class Converter;}
namespace dat::atr::normal{class Structured;}
namespace dat::atr{class Location;}
namespace thr::task{class Pool;}


namespace dyn::prc::cloud{

class Normal
{
public:
  // Constructor / Destructor
  Normal(dyn::prc::Node* node_processing);
  ~Normal();

public:
  //Main function
  void start_thread(std::shared_ptr<dat::base::Sensor> sensor);
  void run_thread(std::shared_ptr<dat::base::Sensor> sensor);
  void wait_thread();

  //Subfunction
  void compute_normal(std::shared_ptr<dat::base::Sensor> sensor);
  void compute_image(std::shared_ptr<dat::base::Sensor> sensor);

private:
  dyn::prc::Structure* dyn_struct;
  dat::img::Image* dat_image;
  dat::elm::Glyph* dat_glyph;
  dat::atr::normal::Structured* atr_normal;
  dat::img::Converter* img_converter;
  dat::atr::Location* atr_location;
  thr::task::Pool* thread_pool;

  std::thread thread;
  bool thread_idle = true;
};

}
