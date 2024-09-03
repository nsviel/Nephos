#include "Slider.h"

#include <Data/Player/Namespace.h>
#include <Data/Graph/Namespace.h>
#include <Data/Element/Namespace.h>
#include <Data/Base/Namespace.h>


namespace dat::ply{

//Constructor / Destructor
Slider::Slider(dat::ply::Node* node_player){
  //---------------------------

  dat::gph::Node* node_graph = node_player->get_node_graph();

  this->ply_struct = node_player->get_ply_struct();
  this->ply_state = node_player->get_ply_state();
  this->gph_selection = node_graph->get_gph_selection();

  //---------------------------
}
Slider::~Slider(){}

//Main function
void Slider::slider_query(float value){
  std::shared_ptr<dat::base::Set> set = gph_selection->get_selected_set();
  if(!set) return;
  //---------------------------

  ply_state->manage_query(*set, value);

  //---------------------------
}
void Slider::slider_hold(float value){
  //---------------------------

  if(ply_struct->state.query != value){
    ply_struct->state.query = value;

    std::shared_ptr<dat::base::Set> set = gph_selection->get_selected_set();
    if(!set) return;
    ply_state->manage_state(*set);
  }

  //---------------------------
}

}
