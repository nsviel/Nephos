#include "Button.h"

#include <Data/Player/Namespace.h>
#include <Data/Graph/Namespace.h>
#include <Data/Element/Namespace.h>
#include <Data/Base/Namespace.h>


namespace dat::ply{

//Constructor / Destructor
Button::Button(dat::ply::Node* node_player){
  //---------------------------

  dat::gph::Node* node_graph = node_player->get_node_graph();

  this->ply_struct = node_player->get_ply_struct();
  this->ply_state = node_player->get_ply_state();
  this->gph_selection = node_graph->get_gph_selection();
  this->gph_element = node_graph->get_gph_element();

  //---------------------------
}
Button::~Button(){}

//Main function
void Button::button_query(float value){
  dat::base::Set* set = gph_selection->get_selected_set();
  if(set == nullptr) return;
  //---------------------------

  ply_state->manage_query(set, value);
  ply_struct->state.query = true;

  //---------------------------
}
void Button::button_play(){
  dat::base::Set* set = gph_selection->get_selected_set();
  if(set == nullptr) return;
  //---------------------------

  if(!ply_struct->state.play){
    ply_struct->state.play = true;
    ply_struct->state.pause = false;
  }else{
    ply_struct->state.pause = false;
  }

  ply_state->manage_state(set);

  //---------------------------
}
void Button::button_pause(){
  dat::base::Set* set = gph_selection->get_selected_set();
  if(set == nullptr) return;
  //---------------------------

  ply_struct->state.pause = !ply_struct->state.pause;

  ply_state->manage_state(set);

  //---------------------------
}
void Button::button_stop(){
  dat::base::Set* set = gph_selection->get_selected_set();
  if(set == nullptr) return;
  //---------------------------

  ply_struct->state.play = false;
  ply_struct->state.pause = true;
  timestamp.current = timestamp.begin;

  ply_state->manage_state(set);
  ply_state->manage_restart(set);

  //---------------------------
}
void Button::button_replay(){
  //---------------------------

  ply_struct->state.replay = !ply_struct->state.replay;

  //---------------------------
}
void Button::button_record(){
  dat::base::Set* set = gph_selection->get_selected_set();
  if(set == nullptr) return;
  //---------------------------

  ply_struct->state.record = !ply_struct->state.record;

  ply_state->manage_state(set);

  //---------------------------
}
void Button::button_lock(bool value){
  dat::base::Set* set = gph_selection->get_selected_set();
  if(set == nullptr) return;
  //---------------------------

  set->is_locked = value;

  //---------------------------
}
void Button::button_close(){
  dat::base::Set* set = gph_selection->get_selected_set();
  if(set == nullptr) return;
  //---------------------------

  gph_element->remove_active_entity(set);

  //---------------------------
}
void Button::button_forward(float value){
  dat::base::Set* set = gph_selection->get_selected_set();
  if(set == nullptr) return;
  //---------------------------

  float ts_forward = timestamp.current + 5 * value;
  if(ts_forward > timestamp.end) ts_forward = timestamp.end;
  if(ts_forward < timestamp.begin) ts_forward = timestamp.begin;

  ply_state->manage_query(set, ts_forward);

  //---------------------------
}

}
