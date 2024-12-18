#pragma once

#include "../Base/struct_voxelMap.h"
#include "../Base/common.h"

class Node_engine;
class Scene;
class Object;
class Configuration;

class SLAM_init;
class SLAM_optim;
class SLAM_assessment;
class SLAM_map;
class SLAM_parameter;
class SLAM_normal;
class SLAM_transform;
class SLAM_glyph;
class SLAM_sampling;


namespace slam::remade{

class SLAM
{
public:
  //Constructor / Destructor
  SLAM(Node_engine* node);
  ~SLAM();

public:
  void update_configuration();
  bool compute_slam(Collection* collection, int subset_ID);
  void reset_slam();
  void print_result();

  inline Node_engine* get_node_core(){return node_core;}
  inline SLAM_normal* get_slam_normal(){return slam_normal;}
  inline SLAM_optim* get_slam_optim(){return slam_optim;}
  inline SLAM_assessment* get_slam_assess(){return slam_assess;}
  inline SLAM_map* get_slam_map(){return slam_map;}
  inline SLAM_parameter* get_slam_param(){return slam_param;}
  inline SLAM_transform* get_slam_transf(){return slam_transf;}
  inline SLAM_glyph* get_slam_glyph(){return slam_glyph;}
  inline SLAM_sampling* get_slam_sampling(){return slam_sampling;}

  inline void set_nb_thread(int value){this->nb_thread = value;}

private:
  bool check_condition(Collection* collection, int subset_ID);
  void compute_finalization(Collection* collection, int subset_ID, bool success, float t_begin);
  void compute_transform_subset(Cloud* cloud);
  void compute_transform_glyph(Cloud* cloud);
  void reset_visibility(Collection* collection, int subset_ID);

private:
  Node_engine* node_core;
  Scene* sceneManager;
  Configuration* configManager;

  //SLAM_optim_ceres* ceresManager;
  SLAM_init* slam_init;
  SLAM_optim* slam_optim;
  SLAM_normal* slam_normal;
  SLAM_assessment* slam_assess;
  SLAM_map* slam_map;
  SLAM_parameter* slam_param;
  SLAM_transform* slam_transf;
  SLAM_glyph* slam_glyph;
  SLAM_sampling* slam_sampling;

  float time_slam;
  std::string lidar_model;
  int nb_thread;
};

}
