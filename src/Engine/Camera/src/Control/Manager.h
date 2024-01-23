#pragma once


#include <Engine/Camera/Namespace.h>
#include <Utility/Specific/common.h>

class Engine;


namespace camera::src{

class Manager
{
public:
  Manager(Engine* engine);
  ~Manager();

public:
  //Main function
  void create_camera();
  void reset();

  inline entity::Camera* get_camera(int i){return vec_camera[i];}
  inline entity::Camera* get_current_camera(){return current_camera;}

private:
  Engine* engine;
  vector<entity::Camera*> vec_camera;
  entity::Camera* current_camera;

  int camera_ID;
};

}
