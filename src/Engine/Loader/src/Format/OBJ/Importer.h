#pragma once

#include <Loader/src/Base/Importer.h>
#include <Utility/Specific/Common.h>
#include <Utility/Function/File/Path.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <fstream>


namespace format::obj{

struct Vertex{
  //---------------------------

  glm::vec3 location;
  glm::vec2 texcoord;
  glm::vec3 normal;

  //---------------------------
};
struct Vertex_ref{
  //---------------------------

  Vertex_ref( int v, int vt, int vn ) : v(v), vt(vt), vn(vn) { }
  int v, vt, vn;

  //---------------------------
};

class Importer : public utl::type::Importer
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  //Main function
  utl::File* import(utl::Path path);

  //Subfunction
  void init_params();
  std::vector<Vertex> get_data_from_file(std::istream& in);
  void parse_mtl(std::string path_obj);
  void fill_data_file(utl::file::Data* data, std::vector<Vertex>& vertex_vec);

private:
  std::string file_mtl;
  std::string file_texture;
  bool is_face;
};

}
