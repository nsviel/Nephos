#pragma once

#include "../Base/common.h"


namespace slam::remade{
  
class SLAM_sampling
{
public:
  //Constructor / Destructor
  SLAM_sampling();
  ~SLAM_sampling();

public:
  //Sampling functions
  std::vector<glm::vec3> sub_sampling_subset(Cloud* cloud, float voxel_size);
  void grid_sampling_subset(Cloud* cloud);

  inline double* get_min_root_distance(){return &min_root_distance;}
  inline double* get_max_root_distance(){return &max_root_distance;}
  inline double* get_grid_voxel_size(){return &grid_voxel_width;}
  inline int* get_max_keypoint(){return &max_keypoint;}

private:
  double min_root_distance;
  double max_root_distance;
  double grid_voxel_width;
  int max_keypoint;
};


}
