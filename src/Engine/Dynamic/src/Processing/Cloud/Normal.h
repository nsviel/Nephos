#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <thread>

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dat{class Image;}
namespace utl::base{class Data;}
namespace dat::base{class Entity;}
namespace ope::image{class Converter;}
namespace ope::normal{class Structured;}


namespace dyn::cloud{

class Normal
{
public:
  // Constructor / Destructor
  Normal(dyn::Node* node_dynamic);
  ~Normal();

public:
  //Main function
  void start_thread(dat::base::Entity* entity);
  void run_thread(dat::base::Entity* entity);
  void wait_thread();

private:
  dyn::Structure* dyn_struct;
  ope::normal::Structured* ope_normal;
  ope::image::Converter* ope_converter;
  dat::Image* dat_image;

  std::thread thread;
  bool thread_idle = true;
};

}
