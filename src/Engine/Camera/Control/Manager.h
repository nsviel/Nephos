#pragma once

#include <Utility/Base/Namespace.h>
#include <Engine/Camera/Namespace.h>
#include <Utility/Specific/common.h>

class Engine;


namespace eng::camera{

class Manager
{
public:
  Manager(Engine* engine);
  ~Manager();

public:
  //Main function
  void create_camera();
  void reset();

  inline eng::base::Camera* get_camera(int i){return vec_camera[i];}
  inline eng::base::Camera* get_current_camera(){return current_camera;}

private:
  Engine* engine;
  vector<eng::base::Camera*> vec_camera;
  eng::base::Camera* current_camera;

  int camera_ID;
};

}
