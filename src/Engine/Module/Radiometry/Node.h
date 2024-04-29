#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace eng{class Node;}
namespace scene{class Node;}
namespace radio{class Structure;}
namespace radio{class Detection;}
namespace radio{class Model;}

namespace radio::detection{class Identification;}
namespace radio::detection{class Hough;}
namespace radio::detection{class Ransac;}
namespace radio::model{class Measure;}
namespace radio::gui{class Radiometry;}


namespace radio{

class Node : public utl::type::Node
{
public:
  //Constructor / Destructor
  Node(eng::Node* node_engine);
  ~Node();

public:
  //Main function
  void config();
  void init();
  void loop();
  void gui();
  void clean();

  inline eng::Node* get_node_engine(){return node_engine;}
  inline scene::Node* get_node_scene(){return node_scene;}
  inline prf::Node* get_node_profiler(){return node_profiler;}

  inline radio::Structure* get_radio_struct(){return radio_struct;}
  inline radio::Detection* get_radio_detection(){return radio_detection;}
  inline radio::Model* get_radio_model(){return radio_model;}

  inline radio::detection::Identification* get_radio_identification(){return radio_identification;}
  inline radio::detection::Hough* get_radio_hough(){return radio_hough;}
  inline radio::detection::Ransac* get_radio_ransac(){return radio_ransac;}
  inline radio::model::Measure* get_model_measure(){return radio_measure;}


private:
  //Dependancy
  eng::Node* node_engine;
  scene::Node* node_scene;
  prf::Node* node_profiler;

  //Child
  radio::Structure* radio_struct;
  radio::Detection* radio_detection;
  radio::Model* radio_model;
  radio::detection::Identification* radio_identification;
  radio::detection::Hough* radio_hough;
  radio::detection::Ransac* radio_ransac;
  radio::model::Measure* radio_measure;
  radio::gui::Radiometry* gui_radiometry;
};

}
