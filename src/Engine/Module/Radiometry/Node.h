#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace eng{class Node;}
namespace eng::scene{class Node;}
namespace k4n{class Node;}
namespace radio{class Structure;}
namespace radio{class Detection;}
namespace radio{class Model;}

namespace radio::detection{class Detector;}
namespace radio::detection{class Hough;}
namespace radio::model{class Measure;}


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

  inline radio::Structure* get_radio_struct(){return radio_struct;}
  inline radio::Detection* get_radio_detection(){return radio_detection;}
  inline radio::Model* get_radio_model(){return radio_model;}

  inline radio::detection::Detector* get_radio_detector(){return radio_detector;}
  inline radio::detection::Hough* get_radio_hough(){return radio_hough;}
  inline radio::model::Measure* get_model_measure(){return radio_measure;}


private:
  //Dependancy
  eng::Node* node_engine;
  eng::scene::Node* node_scene;
  prf::Node* node_profiler;

  //Child
  radio::Structure* radio_struct;
  radio::Detection* radio_detection;
  radio::Model* radio_model;
  radio::detection::Detector* radio_detector;
  radio::detection::Hough* radio_hough;
  radio::model::Measure* radio_measure;
};

}
