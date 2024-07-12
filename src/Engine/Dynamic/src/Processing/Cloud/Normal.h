#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <thread>

namespace dyn{class Node;}
namespace dyn{class Structure;}
namespace dat::element{class Image;}
namespace dat{class Glyph;}
namespace utl::base{class Data;}
namespace dyn::base{class Sensor;}
namespace ope::image{class Converter;}
namespace ope::normal{class Structured;}
namespace ope::attribut{class Attribut;}
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
  dat::element::Image* dat_image;
  dat::Glyph* dat_glyph;
  ope::normal::Structured* ope_normal;
  ope::image::Converter* ope_converter;
  ope::attribut::Attribut* ope_attribut;
  utl::thread::task::Pool* thread_pool;

  std::thread thread;
  bool thread_idle = true;
};

}
