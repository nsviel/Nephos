#include "UID.h"

#include <Data/Namespace.h>
#include <Camera/Namespace.h>
#include <Dynamic/Namespace.h>


namespace dat{

//Constructor / Destructor
UID::UID(dat::Node* node_data){
  //---------------------------

  this->generator = std::mt19937(std::random_device()());
  this->distribution = std::uniform_int_distribution<int>(1, 1000000);

  //---------------------------
}
UID::~UID(){}

//Main function
int UID::generate_UID(){
  std::lock_guard<std::mutex> lock(mutex);
  //---------------------------

  int new_uid;
  do{
    new_uid = generate_rdm_UID();
  }while(!is_unique(new_uid));

  set_uid.insert(new_uid);

  //---------------------------
  return new_uid;
}

//Subfunction
int UID::generate_rdm_UID(){
  return distribution(generator);
}
bool UID::is_unique(int uid){
  return set_uid.find(uid) == set_uid.end();
}

}
