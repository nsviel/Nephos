#pragma once

#include <memory>

namespace k4n{class Node;}
namespace k4n{class Structure;}
namespace k4n::base{class Sensor;}
namespace k4n::playback{class Sensor;}
namespace dat::base{class Set;}


namespace k4n::gui{

class Playback
{
public:
  //Constructor / Destructor
  Playback(k4n::Node* node_k4n);
  ~Playback();

  //Main function
  void show_parameter(std::shared_ptr<k4n::base::Sensor> sensor);

  //Subfunction
  void show_transformation_mode(std::shared_ptr<dat::base::Set> set);
  void show_firmware_info(std::shared_ptr<k4n::base::Sensor> sensor);
  void show_info_device(std::shared_ptr<k4n::playback::Sensor> sensor);
  void show_info_color(std::shared_ptr<k4n::playback::Sensor> sensor);
  void show_info_depth(std::shared_ptr<k4n::playback::Sensor> sensor);
  void show_info_synch(std::shared_ptr<k4n::playback::Sensor> sensor);

private:
  k4n::Structure* k4n_struct;
  k4n::Node* node_k4n;
};

}
