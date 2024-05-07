#pragma once

#include <Utility/Specific/Common.h>
#include <k4a/k4a.hpp>

namespace k4n{class Node;}
namespace k4n::dev{class Device;}
namespace k4n::utils{class Data;}
namespace k4n::utils{class Configuration;}
namespace rad::detection{class Identification;}
namespace utl::thread{class Pool;}


namespace k4n::processing{

class Image
{
public:
  //Constructor / Destructor
  Image(k4n::Node* node_k4n);
  ~Image();

public:
  //Main function
  void start_thread(k4n::dev::Device* sensor);
  void run_thread(k4n::dev::Device* sensor);
  void wait_thread();

  //Subfunction
  void copy_image(k4n::dev::Device* sensor);
  void copy_image_color(k4n::dev::Device* sensor);
  void copy_image_depth(k4n::dev::Device* sensor);
  void copy_image_ir(k4n::dev::Device* sensor);

private:
  utl::thread::Pool* thread_pool;
  k4n::utils::Data* k4n_data;
  k4n::utils::Configuration* k4n_config;
  rad::detection::Identification* radio_identification;

  bool idle = true;
};

}
