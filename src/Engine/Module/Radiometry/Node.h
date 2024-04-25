#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace eng{class Node;}
namespace eng::scene{class Node;}
namespace k4n{class Node;}
namespace radio::detection{class Detector;}
namespace radio::detection{class Hough;}
namespace radio::calibration{class Model;}
namespace radio::calibration{class Measure;}
namespace radio{class Detection;}


namespace radio{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(k4n::Node* node_k4n);
  ~Node();

public:
  //Main function
  void config();
  void init();
  void loop();
  void gui();
  void clean();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline eng::scene::Node* get_node_scene(){return node_scene;}
  inline prf::Node* get_node_profiler(){return node_profiler;}

  inline radio::detection::Detector* get_k4n_detector(){return k4n_detector;}
  inline radio::detection::Hough* get_k4n_hough(){return k4n_hough;}
  inline radio::calibration::Model* get_k4n_model(){return k4n_model;}
  inline radio::calibration::Measure* get_k4n_measure(){return k4n_measure;}
  inline radio::Detection* get_radio_detection(){return radio_detection;}

private:
  //Dependancy
  eng::Node* node_engine;
  eng::scene::Node* node_scene;
  prf::Node* node_profiler;

  //Child
  radio::detection::Detector* k4n_detector;
  radio::detection::Hough* k4n_hough;
  radio::calibration::Model* k4n_model;
  radio::calibration::Measure* k4n_measure;
  radio::Detection* radio_detection;
};

}
