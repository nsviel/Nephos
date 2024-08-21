#include "Player.h"

#include <Data/Player/Namespace.h>
#include <Data/Graph/Namespace.h>
#include <Data/Element/Namespace.h>
#include <Data/Base/Namespace.h>


namespace dat::ply{

//Constructor / Destructor
Player::Player(dat::ply::Node* node_player){
  //---------------------------

  dat::gph::Node* node_graph = node_player->get_node_graph();

  this->ply_state = node_player->get_ply_state();
  this->gph_selection = node_graph->get_gph_selection();
  this->gph_element = node_graph->get_gph_element();

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::button_query(float value){
  dat::base::Set* set = gph_selection->get_selected_set();
  if(set == nullptr) return;
  //---------------------------

  ply_state->manage_query(set, value);
  state.query = true;

  //---------------------------
}
void Player::button_play(){
  dat::base::Set* set = gph_selection->get_selected_set();
  if(set == nullptr) return;
  //---------------------------

  if(!state.play){
    state.play = true;
    state.pause = false;
  }else{
    state.pause = false;
  }

  ply_state->manage_state(set);

  //---------------------------
}
void Player::button_pause(){
  dat::base::Set* set = gph_selection->get_selected_set();
  if(set == nullptr) return;
  //---------------------------

  state.pause = !state.pause;

  ply_state->manage_state(set);

  //---------------------------
}
void Player::button_stop(){
  dat::base::Set* set = gph_selection->get_selected_set();
  if(set == nullptr) return;
  //---------------------------

  state.play = false;
  state.pause = true;
  timestamp.current = timestamp.begin;

  ply_state->manage_state(set);
  ply_state->manage_restart(set);

  //---------------------------
}
void Player::button_replay(){
  //---------------------------

  state.replay = !state.replay;

  //---------------------------
}
void Player::button_record(){
  dat::base::Set* set = gph_selection->get_selected_set();
  if(set == nullptr) return;
  //---------------------------

  state.record = !state.record;

  ply_state->manage_state(set);

  //---------------------------
}
void Player::button_lock(bool value){
  dat::base::Set* set = gph_selection->get_selected_set();
  if(set == nullptr) return;
  //---------------------------

  set->is_locked = value;

  //---------------------------
}
void Player::button_close(){
  dat::base::Set* set = gph_selection->get_selected_set();
  if(set == nullptr) return;
  //---------------------------

  gph_element->remove_active_entity(set);

  //---------------------------
}
void Player::button_forward(float value){
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
