#include "Player.h"

#include <Velodyne/Namespace.h>


namespace vld{

//Constructor / Destructor
Player::Player(vld::structure::Main* velo_struct){
  //---------------------------

  this->velo_struct = velo_struct;

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::determine_range(){
  if(velo_struct->data.current_set == nullptr) return;
  //---------------------------

  velo_struct->player.idx_beg = 0;
  velo_struct->player.idx_cur = 0;
  velo_struct->player.idx_end = velo_struct->data.current_set->list_entity.size() - 1;

  //---------------------------
}

}
