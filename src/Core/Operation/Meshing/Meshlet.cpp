#include "Meshlet.h"

#include <Utility/Namespace.h>
#include <meshoptimizer.h>
#include <cstdlib>


namespace ope{

// Constructor / Destructor
Meshlet::Meshlet(){
  //---------------------------


  //---------------------------
}
Meshlet::~Meshlet(){}

//Main function
void Meshlet::compute(utl::base::Data& data){
  //---------------------------

  std::vector<glm::vec3>            xyz;
  std::vector<meshopt_Meshlet> vec_meshlet;
  std::vector<uint32_t>        vec_vertice;
  std::vector<uint8_t>         vec_triangle;
  int nb_indices;

  const size_t max_vertice  = 64;
  const size_t max_triangle = 124;
  const float  kConeWeight   = 0.0f;
  const size_t max_meshlet = meshopt_buildMeshletsBound(nb_indices, max_vertice, max_triangle);

  vec_meshlet.resize(max_meshlet);
  vec_vertice.resize(max_meshlet * max_vertice);
  vec_triangle.resize(max_meshlet * max_triangle * 3);
/*
  size_t meshletCount = meshopt_buildMeshlets(
    vec_meshlet.data(),
    vec_vertice.data(),
    vec_triangle.data(),
    reinterpret_cast<const uint32_t*>(mesh.GetTriangles().data()),
    mesh.GetNumIndices(),
    reinterpret_cast<const float*>(mesh.GetPositions().data()),
    mesh.GetNumVertices(),
    sizeof(glm::vec3),
    max_vertice,
    max_triangle,
    kConeWeight);

  auto& last = vec_meshlet[meshletCount - 1];
  vec_vertice.resize(last.vertex_offset + last.vertex_count);
  vec_triangle.resize(last.triangle_offset + ((last.triangle_count * 3 + 3) & ~3));
  vec_meshlet.resize(meshletCount);
*/
  //---------------------------
}

}
