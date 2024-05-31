#pragma once

namespace eng{class Node;}
namespace sce{class Node;}
namespace cam{class Control;}
namespace cam{class Entity;}
namespace dat{class Graph;}
namespace dat{class Set;}
namespace dat{class Node;}
namespace dat::base{class Entity;}
namespace dat::base{class Set;}
namespace dat::base{class Glyph;}
namespace dat::base{class Object;}


namespace dat{

class Glyph
{
public:
  //Constructor / Destructor
  Glyph(dat::Node* node_data);
  ~Glyph();

public:
  //Main function
  void init();

  //Glyph init
  void create_glyph_world();
  void create_glyph_object(dat::base::Object* object);
  void create_glyph_camera(cam::Entity* camera);

  //Glyph creation
  void create_glyph(dat::base::Set* set, dat::base::Glyph* glyph);
  void create_glyph(dat::base::Entity* entity, dat::base::Glyph* glyph);

private:
  eng::Node* node_engine;
  sce::Node* node_scene;
  dat::Node* node_data;
  dat::Graph* dat_graph;
  dat::Set* dat_set;
  cam::Control* cam_control;
};

}
