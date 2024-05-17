#pragma once

#include <glm/glm.hpp>
#include <tsl/robin_map.h>

namespace utl::base{class Data;}

typedef int key;
typedef std::vector<glm::vec4> Voxel;
typedef tsl::robin_map<key, Voxel> Voxel_map;


namespace ope{

class Voxelizer
{
public:
  // Constructor / Destructor
  Voxelizer();
  ~Voxelizer();

public:
  //Main function
  void find_voxel_min_number_of_point(utl::base::Data* data);
  void find_voxel_min_number_of_point(utl::base::Data* data, float voxel_size, int min_nb_point);
  void reconstruct_data_by_goodness(utl::base::Data* data);

  inline void set_voxel_size(float value){this->voxel_size = value;}
  inline void set_minimum_pt_in_voxel(int value){this->min_nb_point = value;}

private:
  Voxel_map voxel_map;
  float voxel_size;
  int min_nb_point;
  int max_nb_point;
};

}
