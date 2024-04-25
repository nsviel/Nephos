#include "Node.h"

#include <K4N/Namespace.h>
#include <Engine/Namespace.h>
#include <Scene/Namespace.h>
#include <Profiler/Namespace.h>
#include <Radiometry/Namespace.h>


namespace radio{

//Constructor / Destructor
Node::Node(k4n::Node* node_k4n){
  //---------------------------

  //Dependancy
  this->node_engine = node_k4n->get_node_engine();
  this->node_scene = node_k4n->get_node_scene();
  this->node_profiler = node_k4n->get_node_profiler();

  this->k4n_hough = new radio::detection::Hough(node_k4n);
  this->k4n_detector = new radio::detection::Detector(node_k4n);
  this->k4n_model = new radio::calibration::Model(node_k4n);
  this->k4n_measure = new radio::calibration::Measure(node_k4n);
  this->k4n_calibration = new radio::calibration::Calibration(node_k4n);

  //---------------------------
}
Node::~Node(){}

//Main function
void Node::config(){
  //---------------------------


  //---------------------------
}
void Node::init(){
  //---------------------------


  //---------------------------
}
void Node::loop(){
  //---------------------------



  //---------------------------
}
void Node::gui(){
  //---------------------------



  //---------------------------
}
void Node::clean(){
  //---------------------------


  //---------------------------
}


}
