#include "Node.h"
/*
#include "src/SLAM.h"
#include "src/SLAM_parameter.h"
#include "GUI/GUI_Slam.h"
#include "ct_icp/CT_ICP.h"

#include "../Node_module.h"

#include "../../Engine/Core/Configuration.h"
#include "../../Engine/Node_engine.h"
#include "../../Scene/Node_scene.h"
#include "../../Operation/Node_operation.h"


namespace slam{

//Constructor / Destructor
Node::Node(Node_module* node){
  this->node_module = node;
  //---------------------------

  this->node_core = node->get_node_core();
  this->node_ope = node_core->get_node_ope();

  this->slamManager = new SLAM(node_core);
  this->cticpManager = new CT_ICP();
  this->slam_param = slamManager->get_slam_param();
  this->gui_slam = new GUI_Slam(this);

  Configuration* configManager = node_core->get_configManager();
  this->with_slam = configManager->parse_json_b("module", "with_slam");
  this->algo = 0;

  //---------------------------
}
Node::~Node(){}

void Node::update(){
  //---------------------------

  slamManager->update_configuration();

  //---------------------------
}
void Node::reset(){
  //---------------------------

  slamManager->reset_slam();
  cticpManager->reset();

  //---------------------------
}
void Node::draw(){
  //---------------------------

  gui_slam->design_SLAM();

  //---------------------------
}
void Node::draw_online(){
  //---------------------------

  gui_slam->design_option();

  //---------------------------
}
void Node::online(Collection* collection, int subset_ID){
  //---------------------------

  if(with_slam){
    if(algo == 0){
      Cloud* cloud = (Cloud*)collection->get_obj_byID(subset_ID);
      cticpManager->algo(cloud);
    }
    else if(algo == 1){
      slamManager->compute_slam(collection, subset_ID);
    }
  }

  //---------------------------
}

}*/
