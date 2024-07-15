#pragma once

#include <IO/src/Import/Structure/Base.h>
#include <Utility/Function/File/Path.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <fstream>


namespace fmt::obj{

struct Vertex{
  //---------------------------

  glm::vec3 location;
  glm::vec2 texcoord;
  glm::vec3 normal;

  //---------------------------
};
struct Vertex_ref{
  //---------------------------

  Vertex_ref( int v, int vt, int vn ) : v(v), vt(vt), vn(vn){ }
  int v, vt, vn;

  //---------------------------
};

class Importer : public ldr::importer::Base
{
public:
  //Constructor / Destructor
  Importer();
  ~Importer();

public:
  //Main function
  utl::base::Element* import(utl::base::Path path);

  //Subfunction
  void init_params();
  std::vector<Vertex> get_data_from_file(std::istream& in);
  void parse_mtl(std::string path_obj);
  void fill_data_file(utl::base::Data* data, std::vector<Vertex>& vertex_vec);

private:
  std::string file_mtl;
  std::string file_texture;
  bool is_face;
};

}
