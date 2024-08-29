#pragma once

#include <memory>
#include <thread>

namespace rad::cor{class Node;}
namespace rad::cor{class Structure;}
namespace dat::base{class Sensor;}
namespace thr::task{class Pool;}
namespace utl::media{class Image;}
namespace rad::cor{class Glyph;}
namespace rad::cor::image{class Hough;}
namespace rad::cor::image{class Image;}
namespace dat::elm{class Image;}


namespace rad::cor::image{

class Detection
{
public:
  //Constructor / Destructor
  Detection(rad::cor::Node* node_correction);
  ~Detection();

public:
  //Main function
  void start_thread(std::shared_ptr<dat::base::Sensor> sensor);
  void run_thread(std::shared_ptr<dat::base::Sensor> sensor);
  void wait_thread();

  //Subfunction
  void make_shape_detection(std::shared_ptr<dat::base::Sensor> sensor, std::shared_ptr<utl::media::Image> image, std::shared_ptr<utl::media::Image> output);

private:
  thr::task::Pool* thread_pool;
  rad::cor::Structure* rad_struct;
  rad::cor::Glyph* rad_glyph;
  rad::cor::image::Hough* rad_hough;
  rad::cor::image::Image* rad_image;
  dat::elm::Image* dat_image;

  std::thread thread;
  bool thread_idle = true;
};

}
