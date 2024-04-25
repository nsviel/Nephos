#include "Node.h"

#include <K4N/Namespace.h>


namespace k4n::matching{

//Constructor / Destructor
Node::Node(k4n::Node* node_k4n){
  //---------------------------

  this->k4n_hough = new k4n::detection::Hough(node_k4n);
  this->k4n_detector = new k4n::detection::Detector(node_k4n);
  this->k4n_model = new k4n::calibration::Model(node_k4n);
  this->k4n_measure = new k4n::calibration::Measure(node_k4n);
  this->k4n_calibration = new k4n::calibration::Calibration(node_k4n);

  //---------------------------
}
Node::~Node(){}

//Main function


}
