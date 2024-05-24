#include "Player.h"

#include <Kinect/Namespace.h>
#include <Utility/Namespace.h>


namespace k4n::gui{

//Constructor / Destructor
Player::Player(k4n::Node* node_k4n){
  //---------------------------

  this->node_k4n = node_k4n;
  this->gui_capture = new k4n::gui::Capture(node_k4n);
  this->gui_playback = new k4n::gui::Playback(node_k4n);

  this->item_width = 100;

  //---------------------------
}
Player::~Player(){}

//Main function
void Player::show_info(k4n::dev::Master* master){
  if(master == nullptr) return;
  //---------------------------



  //---------------------------
}
void Player::show_parameter(k4n::dev::Master* master){
  //---------------------------



  //---------------------------
}

//Subfunction


}
