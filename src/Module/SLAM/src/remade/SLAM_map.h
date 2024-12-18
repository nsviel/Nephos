#pragma once

#include "../Base/struct_voxelMap.h"
#include "../Base/common.h"

class SLAM;
class Scene;
class Pather;
class SLAM_sampling;


namespace slam::remade{

class SLAM_map
{
public:
  //Constructor / Destructor
  SLAM_map(SLAM* slam);
  ~SLAM_map();

public:
  //Main function
  void update_configuration();
  void update_map(Collection* collection, int subset_ID);
  void reset_map();

  //Sub-function
  void add_pointToMap(slamap* map, std::vector<glm::vec3>& xyz);
  void add_pointToMap(slamap* map, Cloud* cloud);
  void add_pointToCloud(slamap* map, Cloud* cloud);
  void save_local_cloud();

  //Voxel specific function
  void end_clearTooFarVoxels(slamap* map, Eigen::Vector3d &pose);

  inline slamap* get_local_map(){return local_map;}
  inline slamap* get_local_cloud(){return local_cloud;}
  inline bool* get_with_local_cloud(){return &with_local_cloud;}

private:
  Scene* sceneManager;
  Pather* patherManager;
  SLAM_sampling* slam_sampling;

  slamap* local_map;
  slamap* local_cloud;
  bool with_local_cloud;
};


}
