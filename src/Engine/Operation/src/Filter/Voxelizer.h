#pragma once

#include <Utility/Specific/common.h>
#include <Engine/Operation/src/Namespace.h>
#include <tsl/robin_map.h>

typedef int key;
typedef std::vector<glm::vec4> Voxel;
typedef tsl::robin_map<key, Voxel> Voxel_map;


namespace eng::ope{

class Voxelizer
{
public:
  // Constructor / Destructor
  Voxelizer();
  ~Voxelizer();

public:
  //Main function
  void find_voxel_min_number_of_point(utl::type::Data* data);
  void reconstruct_data_by_goodness(utl::type::Data* data);

private:
  Voxel_map voxel_map;
  float voxel_size;
  int minimum_pt_in_voxel;
};

}
