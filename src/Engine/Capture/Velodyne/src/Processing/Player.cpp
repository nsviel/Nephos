#include "Player.h"

#include <Velodyne/Namespace.h>


namespace vld{

//Constructor / Destructor
Player::Player(vld::structure::Main* vld_struct){
  //---------------------------

  this->vld_struct = vld_struct;

  //---------------------------
}
Player::~Player(){}

//Main function
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

}