#include "Player.h"

#include <Velodyne/Namespace.h>


namespace vld::processing{

//Constructor / Destructor
Player::Player(vld::Node* node_velodyne){
  //---------------------------

  this->vld_struct = node_velodyne->get_vld_struct();

  //---------------------------
}
Player::~Player(){}

//Main function
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

//Subfunction
void Player::determine_range(){
  if(vld_struct->data.current_set == nullptr) return;
  std::shared_ptr<dat::base::Set> set = vld_struct->data.current_set;
  //---------------------------

  vld_struct->player.idx_beg = 0;
  vld_struct->player.idx_cur = 0;
  vld_struct->player.idx_end = set->list_entity.size() - 1;

  //---------------------------
}
void Player::compute_visibility(){
  if(vld_struct->data.current_set == nullptr) return;
  std::shared_ptr<dat::base::Set> set = vld_struct->data.current_set;
  //---------------------------
/*
  //Set visibility just for wanted subsets
  for(auto& entity : set->list_entity){

    if(i >= vld_struct->player.idx_cur - vld_struct->player.idx_rng + 1 && i <= vld_struct->player.idx_cur){
      //entity->visibility(true);
    }else{
      //entity->visibility(false);
    }
  }
*/
  //---------------------------
}
void Player::forward_index(int index){
  std::shared_ptr<dat::base::Set> set = vld_struct->data.current_set;
  //---------------------------

  if(index >= vld_struct->player.idx_end && vld_struct->player.restart){
    vld_struct->player.idx_cur = vld_struct->player.idx_beg;
  }else if(index < vld_struct->player.idx_beg){
    vld_struct->player.idx_cur = vld_struct->player.idx_beg;
  }else if(index <= vld_struct->player.idx_end){
    vld_struct->player.idx_cur = index;
  }

  //set->active_entity = *next(set->list_entity.begin(), index);

  this->compute_visibility();

  //---------------------------
}


}
