#pragma once

#include <Utility/Specific/Common.h>

namespace k4n{class Node;}
namespace k4n::detection{class Detector;}
namespace k4n::detection{class Hough;}
namespace k4n::calibration{class Model;}
namespace k4n::calibration{class Measure;}
namespace k4n::calibration{class Calibration;}


namespace k4n::matching{

class Node
{
public:
  //Constructor / Destructor
  Node(k4n::Node* node_k4n);
  ~Node();

public:
  //Main function

  inline k4n::detection::Detector* get_k4n_detector(){return k4n_detector;}
  inline k4n::detection::Hough* get_k4n_hough(){return k4n_hough;}
  inline k4n::calibration::Model* get_k4n_model(){return k4n_model;}
  inline k4n::calibration::Measure* get_k4n_measure(){return k4n_measure;}
  inline k4n::calibration::Calibration* get_k4n_calibration(){return k4n_calibration;}

private:
  k4n::detection::Detector* k4n_detector;
  k4n::detection::Hough* k4n_hough;
  k4n::calibration::Model* k4n_model;
  k4n::calibration::Measure* k4n_measure;
  k4n::calibration::Calibration* k4n_calibration;
};

}
