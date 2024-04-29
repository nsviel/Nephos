#pragma once

#include <Utility/Specific/Common.h>

namespace prf{class Node;}
namespace eng{class Node;}
namespace gly{class Node;}
namespace rad{class Structure;}
namespace rad{class Detection;}
namespace rad{class Model;}

namespace rad::detection{class Identification;}
namespace rad::detection{class Hough;}
namespace rad::detection{class Ransac;}
namespace rad::model{class Measure;}
namespace rad::gui{class Radiometry;}


namespace rad{

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
  inline gly::Node* get_node_glyph(){return node_glyph;}
  inline prf::Node* get_node_profiler(){return node_profiler;}

  inline rad::Structure* get_radio_struct(){return radio_struct;}
  inline rad::Detection* get_radio_detection(){return radio_detection;}
  inline rad::Model* get_radio_model(){return radio_model;}

  inline rad::detection::Identification* get_radio_identification(){return radio_identification;}
  inline rad::detection::Hough* get_radio_hough(){return radio_hough;}
  inline rad::detection::Ransac* get_radio_ransac(){return radio_ransac;}
  inline rad::model::Measure* get_model_measure(){return radio_measure;}


private:
  //Dependancy
  eng::Node* node_engine;
  gly::Node* node_glyph;
  prf::Node* node_profiler;

  //Child
  rad::Structure* radio_struct;
  rad::Detection* radio_detection;
  rad::Model* radio_model;
  rad::detection::Identification* radio_identification;
  rad::detection::Hough* radio_hough;
  rad::detection::Ransac* radio_ransac;
  rad::model::Measure* radio_measure;
  rad::gui::Radiometry* gui_radiometry;
};

}
