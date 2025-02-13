#pragma once

#include <memory>

namespace rad::cal{class Node;}
namespace rad::cal{class Structure;}
namespace rad::cal{class Image;}
namespace rad::cal{class Rectangle;}
namespace dat::base{class Sensor;}
namespace thr::task{class Pool;}
namespace utl::base{class Image;}
namespace dat::img{class Image;}


namespace rad::cal{

class Detection
{
public:
  //Constructor / Destructor
  Detection(rad::cal::Node* node_detection);
  ~Detection();

public:
  //Main function
  void start_thread(std::shared_ptr<dat::base::Sensor> sensor);
  void run_thread(std::shared_ptr<dat::base::Sensor> sensor);
  void wait_thread();

  //Subfunction
  void make_shape_detection(std::shared_ptr<dat::base::Sensor> sensor, std::shared_ptr<utl::base::Image> image, std::shared_ptr<utl::base::Image> output);

private:
  thr::task::Pool* thread_pool;
  rad::cal::Structure* rad_struct;
  rad::cal::Image* rad_image;
  rad::cal::Rectangle* rad_rectangle;
  dat::img::Image* dat_image;

  bool thread_idle = true;
};

}
