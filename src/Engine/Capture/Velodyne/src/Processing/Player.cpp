#include "Player.h"

#include <Velodyne/Namespace.h>


namespace vld::processing{

//Constructor / Destructor
Player::Player(vld::structure::Main* vld_struct){
  //---------------------------

  this->vld_struct = vld_struct;

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::start_playback(){
  if(vld_struct->data.current_set == nullptr) return;
  utl::type::Set* set = vld_struct->data.current_set;
  //---------------------------

  vld_struct->thread.playback->start_thread();

  //---------------------------
}
void Player::stop_playback(){
  //---------------------------

  vld_struct->thread.playback->stop_thread();

  //---------------------------
}
void Player::determine_range(){
  if(vld_struct->data.current_set == nullptr) return;
  utl::type::Set* set = vld_struct->data.current_set;
  //---------------------------

  vld_struct->player.idx_beg = 0;
  vld_struct->player.idx_cur = 0;
  vld_struct->player.idx_end = set->list_entity.size() - 1;

  //---------------------------
}
void Player::compute_visibility(){
  if(vld_struct->data.current_set == nullptr) return;
  utl::type::Set* set = vld_struct->data.current_set;
  //---------------------------

  //Set visibility just for wanted subsets
  for(int i=0; i<set->list_entity.size(); i++){
    utl::type::Entity* entity = *next(set->list_entity.begin(), i);

    if(i >= vld_struct->player.idx_cur - vld_struct->player.idx_rng + 1 && i <= vld_struct->player.idx_cur){
      entity->set_visibility(true);
    }else{
      entity->set_visibility(false);
    }
  }

  //---------------------------
}
void Player::forward_index(int index){
  utl::type::Set* set = vld_struct->data.current_set;
  //---------------------------

  if(index >= vld_struct->player.idx_end && vld_struct->player.restart){
    vld_struct->player.idx_cur = vld_struct->player.idx_beg;
  }else if(index < vld_struct->player.idx_beg){
    vld_struct->player.idx_cur = vld_struct->player.idx_beg;
  }else if(index <= vld_struct->player.idx_end){
    vld_struct->player.idx_cur = index;
  }

  set->selected_entity = *next(set->list_entity.begin(), index);

  this->compute_visibility();

  //---------------------------
}

//Player function
void Player::player_pause(bool value){
  //---------------------------

  vld_struct->player.pause = value;

  //---------------------------
}
void Player::player_play(){
  //---------------------------

  if(!vld_struct->player.play){
    vld_struct->player.play = true;
    vld_struct->player.pause = false;
  }else{
    vld_struct->player.pause = false;
  }

  //---------------------------
}
void Player::player_stop(){
  //---------------------------

  vld_struct->player.play = false;
  vld_struct->player.pause = true;
  vld_struct->player.idx_cur = vld_struct->player.idx_beg;

  //---------------------------
}
void Player::player_restart(){
  //---------------------------

  vld_struct->player.restart = !vld_struct->player.restart;

  //---------------------------
}
void Player::player_close(){
  //---------------------------


  //---------------------------
}

}
