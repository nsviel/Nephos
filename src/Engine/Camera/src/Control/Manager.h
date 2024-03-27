#pragma once

#include <Utility/Specific/Common.h>

namespace eng::scene{class Node;}
namespace eng::scene{class Set;}
namespace eng::cam{class Node;}


namespace eng::cam{

class Manager
{
public:
  Manager(eng::cam::Node* node_camera);
  ~Manager();

public:
  //Main function
  void create_camera();
  void reset();

  inline utl::entity::Camera* get_camera(int i){return vec_camera[i];}
  inline utl::entity::Camera* get_current_camera(){return current_camera;}

private:
  eng::scene::Set* sce_set;
  eng::scene::Node* node_scene;
  vector<utl::entity::Camera*> vec_camera;
  utl::entity::Camera* current_camera;

  int camera_ID;
};

}
